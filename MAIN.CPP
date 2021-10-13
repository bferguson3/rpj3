#include <stdio.h>
#include "C:\TC\BIN\RPJ3\IBK.H"
#include <fstream.h>
#include <conio.h>
#include <iostream.h>

#define DSP_GETVER 0xe1
#define DSP_MIDIOUT 0x38
#define SB_FMADDRESS 388h
#define SB_FMDATA 389h

// DOSBOX lengths
typedef unsigned char u8;
//typedef unsigned short u16;
typedef unsigned int u16;
typedef unsigned long u32;
typedef signed char s8;
//typedef signed short s16;
typedef signed int s16;
typedef signed long s32;

u16 SB_BASE;

// RAM
char ibk[3204];
	
//

s16 ResetDSP(void);
void GetChannelType(void);
u8 hex2c(u8 c);
void printVarSizes(void);
void DSP_WriteByte(u8 b);
u8 DSP_ReadByte();
void FM_RegSelect(u8 b);
void FM_RegWrite(u8 b);
void PrintDSPVersion(void);


u8 hex2c(u8 c)
{
	if((c >= '0') && (c <= '9')) return (c-0x30);
	if((c >= 'A') && (c <= 'F')) return (c-0x37);
	if((c >= 'a') && (c <= 'f')) return (c-0x57); 
	return 0;
}

void printVarSizes(void)
{
	printf("sizeof(char): %d\n", sizeof(char));
	printf("sizeof(short): %d\n", sizeof(short));
	printf("sizeof(int): %d\n", sizeof(int));
	printf("sizeof(long): %d\n", sizeof(long));
	printf("sizeof((void*)): %d\n", sizeof(void*));
}

void PrintDSPVersion(void)
{
	u8 ma, mi;
	DSP_WriteByte(DSP_GETVER);
	ma = DSP_ReadByte();
	mi = DSP_ReadByte();
	//printf("Version %d.%d\n", ma, mi);
	if (ma == 1)
		printf("Sound Blaster-compatible detected.\n");
	if (ma == 2)
		printf("Sound Blaster Pro-compatible detected.\n");
	if (ma == 3)
		printf("Sound Blaster 16-compatible detected.\n");
	if (ma == 4) {
		if(mi != 5)
			printf("Sound Blaster AWE32-compatible detected.\n");
		else 
			printf("DOSBOS Sound Blaster detected.\n");
	}
}

void main(int argc, char* argv[])
{
	//printVarSizes();
	s16 i;
	
	SB_BASE=0x0;
	for(i = 0; i < sizeof(argv[1]); i++)
	{
		SB_BASE += hex2c(argv[1][i]) * (0x1 << (4*(sizeof(argv[1])-i)));
	}
	//GetChannelType();

	if(ResetDSP() == 0)
		printf("DSP init OK!\n");
	else
	{
		printf("SB DSP init failed. Exiting.\n");
		return;
	}

	PrintDSPVersion();

	// Load OPL general midi instrument bank
	ifstream f;
	i = 0;
	f.open("GMOPL.IBK", ios::binary|ios::in);
	while((!f.eof()))
		f.read((char*)&ibk[0] + i++, 1);
	f.close();
	IBKFMT* ibkFile = (IBKFMT*)&ibk[0];
	
	// TEST
	/*
	FM_RegSelect(0x20);
	FM_RegWrite(1);
	FM_RegSelect(0x23);
	FM_RegWrite(1);
	FM_RegSelect(0x40);
	FM_RegWrite(0x10);
	FM_RegSelect(0x43);
	FM_RegWrite(0);
	FM_RegSelect(0x60);
	FM_RegWrite(0xf0);
	FM_RegSelect(0x63);
	FM_RegWrite(0xf0);
	FM_RegSelect(0xA0);
	FM_RegWrite(0x98);
	FM_RegSelect(0xB0);
	FM_RegWrite(0x31);
	printf("Press a key to stop this annoying sound\n");
	getchar();
	FM_RegSelect(0xb0);
	FM_RegWrite(0x0);
	*/
	for(i = 62; i < 63; i++)
		printf("Instrument %d: %s\n", i, ibkFile->name[i]);
}
/*
The groupings of twenty-two registers (20-35, 40-55, etc.) have an odd
order due to the use of two operators for each FM voice.  The following
table shows the offsets within each group of registers for each operator.


   Channel        1   2   3   4   5   6   7   8   9
   Operator 1    00  01  02  08  09  0A  10  11  12
   Operator 2    03  04  05  0B  0C  0D  13  14  15
 |   The most accurate method of producing the delay is to read the register
 |   port six times after writing to the register port, and read the register
 |   port thirty-five times after writing to the data port.
 */

void FM_RegSelect(u8 b)
{
	//u8 f;
	asm{
		mov dx,SB_FMADDRESS
		mov al,[b]
		out dx,al
		mov bl,6
	}
	sixwait:
	asm {
		in al,dx
		dec bl 
		jnz sixwait
	}
}

void FM_RegWrite(u8 b)
{
	asm {
		mov dx,SB_FMDATA
		mov al,[b]
		out dx,al 
		mov bl,35
		mov dx,SB_FMADDRESS
	}
	tfwait:
	asm {
		in al,dx 
		dec bl 
		jnz tfwait 
	}
}

// Write to 22Ch
void DSP_WriteByte(u8 b)
{
	asm{
		mov dx,[SB_BASE]
		add dl,0ch
	}
	_dwbb:
	asm{
		in al,dx 
		or al,al 
		js _dwbb
		mov al,[b]
		out dx,al
	}
}

// Read from 22Ah
u8 DSP_ReadByte()
{
	u8 b;
	asm{
		mov dx,[SB_BASE]
		add dl,0eh
	}
	_drbb:
	asm {
		in al,dx
		or al,al
		jns _drbb
		sub dl,4
		in al,dx
		mov [b],al
	} 
	return b;
}


s16 ResetDSP(void)
{
	u8 retries;
	// write 1 to port 226
	asm{
		mov dx,[SB_BASE]
		add dl,6
		mov al,1
		out dx,al
		sub al,al
	}
	// set al to 0, then jp loop 65k times, then output 0 to dx and clear carry
	delay:
	asm{
		dec al
		jnz delay
		out dx,al
		sub cx,cx
		mov bl,255
	}
	// read in from 22e until it is not 0, then read from 22a until 'aah' (ready) is found
	empty:
	asm{
		mov dx,[SB_BASE]
		add dl,0eh
		in al,dx
		or al,al
		jns try_again
		sub dl,4
		in al,dx
		cmp al,0aah
		je ResetOK
	}
	try_again: //asm loop empty;
	asm {
		dec bl 
		jnz empty 
		jmp _notok 
	}
	ResetOK:
	asm mov [retries],bl;
	printf("(It took me %d loops!)\n", 255-retries);
	return 0;

	_notok:
	printf("Could not initialize SB on port %x.\n", SB_BASE);
	return 1;
}

void GetChannelType(void)
{
	u8 optype;
	asm {
		mov dx,SB_FMADDRESS
		in al,dx
		mov [optype],al
	}
	if(optype == 0)
		printf("Four-op card detected.\n");
	else if(optype == 6)
		printf("Two-op card detected.\n");
}