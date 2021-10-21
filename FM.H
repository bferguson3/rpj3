#define DSP_GETVER 0xe1
#define DSP_MIDIOUT 0x38
#define SB_FMADDRESS 388h
#define SB_FMDATA 389h


s16 ResetDSP(void);
void GetChannelType(void);
void DSP_WriteByte(u8 b);
u8 DSP_ReadByte();
void FM_RegSelect(u8 b);
void FM_RegWrite(u8 b);
void PrintDSPVersion(void);
u8 FM_ReadStatus(void);
void FM_SetInstrument(u8 ino);
void FM_AdlibReset(void);

extern char ibk[3204];
u16 SB_BASE;

void FM_AdlibReset(void)
{
	u8 st, ste;
	FM_RegSelect(4);
	FM_RegWrite(0x60);
	FM_RegSelect(4);
	FM_RegWrite(0x80);
	st = FM_ReadStatus();
	FM_RegSelect(2);
	FM_RegWrite(0xff);
	FM_RegSelect(4);
	FM_RegWrite(0x21);
	for(u16 j = 0; j < 0xffff; j++){ j = j; }
	ste = FM_ReadStatus();
	FM_RegSelect(4);
	FM_RegWrite(0x60);
	FM_RegSelect(4);
	FM_RegWrite(0x80);
	if((st & 0xe0) == 0)
		if((ste & 0xe0) == 0xc0)
			printf("Adlib-compatible card detected.\n");
}

void FM_SetInstrument(u8 ino)
{
	IBKFMT* ibkFile = (IBKFMT*)&ibk[0];

	FM_RegSelect(0x20);
	FM_RegWrite(ibkFile->snd[ino].modchar);
	FM_RegSelect(0x23);
	FM_RegWrite(ibkFile->snd[ino].carchar);
	FM_RegSelect(0x40);
	FM_RegWrite(ibkFile->snd[ino].modscal);
	FM_RegSelect(0x43);
	FM_RegWrite(ibkFile->snd[ino].carscal);
	FM_RegSelect(0x60);
	FM_RegWrite(ibkFile->snd[ino].modad);
	FM_RegSelect(0x63);
	FM_RegWrite(ibkFile->snd[ino].carad);
	FM_RegSelect(0x80);
	FM_RegWrite(ibkFile->snd[ino].modsr);
	FM_RegSelect(0x83);
	FM_RegWrite(ibkFile->snd[ino].carsr);
	FM_RegSelect(0xe0);
	FM_RegWrite(ibkFile->snd[ino].modwave);
	FM_RegSelect(0xe3);
	FM_RegWrite(ibkFile->snd[ino].carwave);
}

void FM_RegSelect(u8 b)
{
	//u8 f;
	asm{
		mov dx,SB_FMADDRESS
		mov al,[b]
		out dx,al
#ifdef FASTMODE
		mov bl,60
#else
		mov bl, 6
#endif
	}
	sixwait:
	asm {
		in al,dx
		nop
		nop
		nop
		nop
		nop
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
#ifdef FASTMODE
		mov bx,350
#else 
		mov bx, 35
#endif 
		mov dx,SB_FMADDRESS
	}
	tfwait:
	asm {
		in al,dx 
		nop
		nop
		nop
		nop
		nop
		dec bx 
		jnz tfwait 
	}
}

u8 FM_ReadStatus(void)
{
	u8 c;
	asm { 
		mov dx,388H
		in al,dx 
		mov [c],al
	}
	return c;
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
			printf("DOSBOX Sound Blaster detected.\n");
	}
}
