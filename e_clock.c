#include "pub.h"

typedef struct {
	t_s3c2440_reg  LOCKTIME ;	//0x4c000000
	t_s3c2440_reg  MPLLCON ;	//0x4c000004
	t_s3c2440_reg  UPLLCON ;	//0x4c000008
	t_s3c2440_reg  CLKCON ;		//0x4c00000c
	t_s3c2440_reg  CLKSLOW ;	//0x4c000010
	t_s3c2440_reg  CLKDIVN ;	//0x4c000014
	t_s3c2440_reg  CAMDIVN ;	//0x4c000018
}S3C2440_CLOCK;

static S3C2440_CLOCK * mCLOCK = (S3C2440_CLOCK *)0x4c000000;

volatile unsigned long * pMPLLCON;
volatile unsigned long * pCLKDIVN;

void configClock(void) {
	pMPLLCON = (volatile unsigned long * ) 0x4c000004;// &mCLOCK->MPLLCON;
	pCLKDIVN = (volatile unsigned long * ) 0x4c000014;//&mCLOCK->CLKDIVN;

	*pCLKDIVN = 0x3;

	__asm__ (
			"mrc  p15,0,r0,c1,c0,0 \n"
			"orr  r0,r0,#0xc0000000 \n"
			"mcr  p15,0,r0,c1,c0,0 \n"
			);

	*pMPLLCON = (0x5c << 12 | 1 << 4 | 2 << 0);

}
