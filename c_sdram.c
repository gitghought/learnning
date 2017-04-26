#include "sdram.h"

static S3C2440_SDRAM * mSDRAM = (S3C2440_SDRAM *)0x48000000;

static volatile unsigned long * pBWSCON  ;
static volatile unsigned long * pBWSCON  ;
static volatile unsigned long * pBANKCON0 ;
static volatile unsigned long * pBANKCON1 ;
static volatile unsigned long * pBANKCON2 ;
static volatile unsigned long * pBANKCON3 ;
static volatile unsigned long * pBANKCON4 ;
static volatile unsigned long * pBANKCON5 ;
static volatile unsigned long * pBANKCON6 ;
static volatile unsigned long * pBANKCON7 ;
static volatile unsigned long * pREFRESH  ;
static volatile unsigned long * pBANKSIZE ;
static volatile unsigned long * pMRSRB6  ;
static volatile unsigned long * pMRSRB7  ;

void configSDRAM (void) {
	pBWSCON  = (volatile unsigned long *)&mSDRAM->BWSCON;
	pBANKCON0 = (volatile unsigned long *)&mSDRAM->BANKCON0;
	pBANKCON1 = (volatile unsigned long *)&mSDRAM->BANKCON1;
	pBANKCON2 = (volatile unsigned long *)&mSDRAM->BANKCON2;
	pBANKCON3 = (volatile unsigned long *)&mSDRAM->BANKCON3;
	pBANKCON4 = (volatile unsigned long *)&mSDRAM->BANKCON4;
	pBANKCON5 = (volatile unsigned long *)&mSDRAM->BANKCON5;
	pBANKCON6 = (volatile unsigned long *)&mSDRAM->BANKCON6;
	pBANKCON7 = (volatile unsigned long *)&mSDRAM->BANKCON7;
	pREFRESH  = (volatile unsigned long *)&mSDRAM->REFRESH ;
	pBANKSIZE = (volatile unsigned long *)&mSDRAM->BANKSIZE;
	pMRSRB6  = (volatile unsigned long *)&mSDRAM->MRSRB6 ;
	pMRSRB7  = (volatile unsigned long *)&mSDRAM->MRSRB7 ;

	*pBWSCON  =	0x22011110;
	*pBANKCON0 =	0x00000700;
	*pBANKCON1 =	0x00000700;
	*pBANKCON2 =	0x00000700;
	*pBANKCON3 =	0x00000700;
	*pBANKCON4 =	0x00000700;
	*pBANKCON5 =	0x00000700;
	*pBANKCON6 =	0x00018005;
	*pBANKCON7 =	0x00018005;
	//*pREFRESH  =	0x008C07A3;
	*pREFRESH  =	0x008C04e1;
	*pBANKSIZE =	0x000000B1;
	*pMRSRB6  =	0x00000030;
	*pMRSRB7  =	0x00000030;
}
