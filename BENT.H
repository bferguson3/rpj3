#include <FSTREAM.H>
//#include <IOSTREAM.H>
//#include <IO.H>
#include <STDLIB.H>
//#include <CONIO.H>
//#include <STDIO.H>

#ifndef _BENT_H_
#define _BENT_H_

#ifndef _DOSBOXTYPES_
#define _DOSBOXTYPES_
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef signed char s8;
typedef signed int s16;
typedef signed long s32;
#endif

#include "rpj3\KEYSCAN.H"
#include "rpj3\EGACLR.H"
#include "rpj3\FM.H"

#define TRUE 1
#define True TRUE 
#define true True 
#define FALSE 0
#define False FALSE 
#define false False 
#define BIT(n) (1 << n)

// DOS video modes
#define SetVideoMode(MO) asm { mov ax,MO }; \
	asm { int 0x10 }
#define set_di_coord(x,y) asm { mov di,(80*y)+(x/8) };

// Basically sets color
#define SetVGAPlaneMask(PL) asm { mov dx, 0x3c4 }; \
	asm{mov al, 2 };\
	asm{out dx, al };\
	asm{inc dx };\
	asm{mov al, PL };\
	asm{out dx, al }
// 1 = this bit write enabled to VRAM
// 0 = this bit will not write
#define SetVGABitmask(BL) asm { mov dx, 0x3ce }; \
	asm { mov al, 8 };\
	asm { out dx, al};\
	asm { inc dx};\
	asm{mov al,BL};\
	asm{out dx,al};
#define SetVGASegment() asm { mov ax,0a000h};\
	asm{mov es,ax};
#define EGA_WriteByte(X, Y, DB) asm{mov di, (Y*80)+(X)};\
	asm{mov al,[es:di]};\
	asm{mov al,DB};\
	asm{mov [es:di],al};

u8 hex2c(u8 c);
u16 file2buf(char* filename, char* buffer);
void printVarSizes(void);
u8 read_key(void);
void plotpixel(int x, int y, u8 col);
void WaitVBlank(void);

void WaitRetrace(void)
{
	_vrtwait:
	asm {
		mov dx, 0x3da 
		in al, dx 
		and al, 8 
		jz _vrtwait 
	}
}

void WaitVBlank(void){
	_vblwait:
	asm { 
		mov dx, 0x3da 
		in al, dx 
		and al,8
		jnz _vblwait
	}
}
unsigned char read_key(void)
{
   //8255 PPI uses ports 60h and 61h for kb control
   unsigned char KB_STATE;
   asm {
       in al, 60h     // read keyboard state into al
       mov KB_STATE, al     //and write to var
       in al, 61h    // get kb control state
       or al, 128
       out 61h, al   // keyboard ack
       xor al, 128
       out 61h, al   // reset PB control
   }
   return KB_STATE;
}

// bios routine, void if possible
void plotpixel(int x, int y, u8 col) 
{
	asm {
		mov ah, 0x0C
		mov al, [col]
		mov cx, [x]
		mov dx, [y]
		mov bh, 0
		int 0x10
	}
}

void printVarSizes(void)
{
	printf("sizeof(char): %d\n", sizeof(char));
	printf("sizeof(short): %d\n", sizeof(short));
	printf("sizeof(int): %d\n", sizeof(int));
	printf("sizeof(long): %d\n", sizeof(long));
	printf("sizeof((void*)): %d\n", sizeof(void*));
}

u8 hex2c(u8 c)
{
	if((c >= '0') && (c <= '9')) return (c-0x30);
	if((c >= 'A') && (c <= 'F')) return (c-0x37);
	if((c >= 'a') && (c <= 'f')) return (c-0x57);
	return 0;
}

u16 file2buf(char* filename, char* buffer)
{
	u16 i;
	ifstream f;
	i = 0;
	f.open(filename, ios::binary|ios::in);
	f.seekg(0, ios::end);
	f.seekg(0);
	while(!f.eof())
		f.read(&buffer[i++], 1);
	f.close();
	return i - 1;
}

#endif
