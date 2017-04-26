#include "pub.h"


volatile unsigned int * pNFCONF;
volatile unsigned int * pNFCONT; 
volatile unsigned char  * pNFCMD;  
volatile unsigned char  * pNFADDR; 
volatile unsigned char  * pNFDATA; 
volatile unsigned short * pNFMECCD0;
volatile unsigned short * pNFMECCD1;
volatile unsigned short * pNFSECCD;
volatile unsigned char  * pNFSTAT; 
volatile unsigned short * pNFESTAT0;
volatile unsigned short * pNFESTAT1;
volatile unsigned short * pNFMECC0;
volatile unsigned short * pNFMECC1;
volatile unsigned short * pNFSECC; 
volatile unsigned short * pNFSBLK; 
volatile unsigned short * pNFEBLK; 

void chipWaitIdle(void);
void chipSelect(void);
void chipWait(void);

typedef struct {
	t_s3c2440_reg NFCONF;	
	t_s3c2440_reg NFCONT;	
	t_s3c2440_reg NFCMD;
	t_s3c2440_reg NFADDR;	
	t_s3c2440_reg NFDATA;	
	t_s3c2440_reg NFMECCD0;	
	t_s3c2440_reg NFMECCD1;	
	t_s3c2440_reg NFSECCD;	
	t_s3c2440_reg NFSTAT;	
	t_s3c2440_reg NFESTAT0;	
	t_s3c2440_reg NFESTAT1;	
	t_s3c2440_reg NFMECC0;	
	t_s3c2440_reg NFMECC1;	
	t_s3c2440_reg NFSECC;	
	t_s3c2440_reg NFSBLK;	
	t_s3c2440_reg NFEBLK;	
} S3C2440_NAND;

typedef struct {
	void (* nf_chip_select)();
	void (* nf_chip_wait) (void);
	void (* nf_chip_wait_idle) (void);
} S3C2440_NAND_METHOD;

static S3C2440_NAND * mNand  = (S3C2440_NAND *) 0x4E000000;
static S3C2440_NAND_METHOD method;

void initNand(void) {
}

void chipWaitIdle(void) {
	pNFSTAT   = (volatile unsigned char  * ) 0x4e000020;//&mNand->NFSTAT;	//0x4e000020
	int stat;

	stat = 0;
	while (1) {
		stat = *pNFSTAT & (1 << 0);
		if (stat == 0) {
			break;
		}
		chipWait();
	}
}

void chipWait(void) {
	int i = 0;
	for (i = 0; i < 10; i++) {
		;
	}
}

#if 1
void chipSelect(void) {
	// pNFCONF   = (volatile unsigned int * ) 0x4e000000;//&mNand->NFCONF;	//0x4e000000
	*pNFCONT &= ~(1 << 1);
	chipWait();
}
void chipDiSelect (void) {
	 //pNFCONT   = (volatile unsigned int * ) 0x4e000004;//&mNand->NFCONT;	//0x4e000004
	*pNFCONT |= (1 << 1);
	chipWait();
}

void chipCommand (int cmd) {
	 pNFCMD    = (volatile unsigned char  * ) 0x4e000008;//&mNand->NFCMD;	//0x4e000008
	 //
//	 volatile unsigned char  * pNFCMD = (volatile unsigned char *) &mNand->NFCMD;

	*pNFCMD = cmd;
}

void chipAddress(unsigned int addr) {
	//pNFADDR   = (volatile unsigned char  * ) 0x4e00000c;//&mNand->NFADDR;	//0x4e00000c
	pNFADDR   = (volatile unsigned char  * )  &mNand->NFADDR;	//0x4e00000c

	*pNFADDR = addr & 0xff;
	chipWait();
	*pNFADDR = (addr >> 8) & 0xf;
	chipWait();
	*pNFADDR = (addr >> 11) & 0xff;
	chipWait();
	*pNFADDR = (addr >> 19) & 0xff;
	chipWait();
	*pNFADDR = (addr >> 27) & 0x1;
	chipWait();
}
void chipAddressV2 (unsigned int addr) {
//	pNFADDR   = (volatile unsigned char  * ) 0x4e00000c;//&mNand->NFADDR;	//0x4e00000c

	unsigned int col = addr & 2047;
	unsigned int page = addr / 2048;

	*pNFADDR = col & (0xff);
	chipWait();

	*pNFADDR = (col >> 8) & (0xf);
	chipWait();

	*pNFADDR = (page ) & (0xff);
	chipWait();

	*pNFADDR = (page >> 8) & (0xff);
	chipWait();

	*pNFADDR = (page >> 16) & (0x3);
	chipWait();
}

void chipReset(void) {
	chipSelect();
	chipCommand(0xff);


	chipWait();
	//chipWaitIdle();	
	chipDiSelect();
}

unsigned char  chipReadData(void) {
//	pNFDATA   = (volatile unsigned char  * ) 0x4e000010;//&mNand->NFDATA;	//0x4e000010
	return *pNFDATA;
}

void chipRead(unsigned char * buf, unsigned long start_addr, int size) {

	pNFDATA   = (volatile unsigned char  * ) 0x4e000010;//&mNand->NFDATA;	//0x4e000010
	unsigned long i;
	unsigned long j;

	chipSelect();

	for (i = start_addr; i < start_addr + size; ) {

		chipCommand(0x00);
		chipAddress(i);
		chipCommand(0x30);
		chipWaitIdle();

		for (j = 0; j < 2048; j++, i++) {
			*buf = chipReadData();
			buf++;
		}
	}

	chipDiSelect();
}
#endif

void configNandSub() {

	 pNFCONF   = (volatile unsigned int * ) 0x4e000000;//&mNand->NFCONF;	//0x4e000000
	 pNFCONT   = (volatile unsigned int * ) 0x4e000004;//&mNand->NFCONT;	//0x4e000004

	*pNFCONF = 0 << 12 | 3 << 8 | 2 << 4;
	*pNFCONT = 1 << 4 | 1 << 1 | 1 << 0;
}
void configNand(void) {

	pNFCONF   = (volatile unsigned int * ) 0x4e000000;//&mNand->NFCONF;	//0x4e000000
	pNFCONT   = (volatile unsigned int * ) 0x4e000004;//&mNand->NFCONT;	//0x4e000004
	//pNFCMD    = (volatile unsigned char  * ) 0x4e000008;//&mNand->NFCMD;	//0x4e000008
	pNFADDR   = (volatile unsigned char  * ) 0x4e00000c;//&mNand->NFADDR;	//0x4e00000c

	pNFDATA   = (volatile unsigned char  * ) 0x4e000010;//&mNand->NFDATA;	//0x4e000010
	pNFMECCD0 = (volatile unsigned short * ) &mNand->NFMECCD0;	//0x4e000014
	pNFMECCD1 = (volatile unsigned short * ) &mNand->NFMECCD1;	//0x4e000018
	pNFSECCD  = (volatile unsigned short * ) &mNand->NFSECCD;	//0x4e00001c

	pNFSTAT   = (volatile unsigned char  * ) 0x4e000020;//&mNand->NFSTAT;	//0x4e000020
	pNFESTAT0 = (volatile unsigned short * ) &mNand->NFESTAT0;	//0x4e000024
	pNFESTAT1 = (volatile unsigned short * ) &mNand->NFESTAT1;	//0x4e000028
	pNFMECC0  = (volatile unsigned short * ) &mNand->NFMECC0;	//0x4e00002c

	pNFMECC1  = (volatile unsigned short * ) &mNand->NFMECC1;	//0x4e000030
	pNFSECC   = (volatile unsigned short * ) &mNand->NFSECC;	//0x4e000034
	pNFSBLK   = (volatile unsigned short * ) &mNand->NFSBLK;	//0x4e000038
	pNFEBLK   = (volatile unsigned short * ) &mNand->NFEBLK;	//0x4e00003c

	configNandSub();

	chipReset();
}
