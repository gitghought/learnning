#include "pub.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	void * (*ledOn)(void *);
}t_method_led;

int * ledOn (int * p) ;

typedef struct {
	t_s3c2440_reg GPFCON;
	t_s3c2440_reg GPFDAT;
	t_s3c2440_reg GPFUP;
}S3C2440_GPF;

static S3C2440_GPF * mGPF = (S3C2440_GPF *)0x56000050;

static volatile unsigned short * pGPFCON;
static volatile unsigned char * pGPFDAT;
static volatile unsigned short * pGPFUP ;

t_method_led eLed;

void configLed(void) {
	pGPFCON = (volatile unsigned short *)&mGPF->GPFCON;
	pGPFDAT = (volatile unsigned char *)&mGPF->GPFDAT;
	*pGPFCON = (1 << 8) | (1 << 10) | (1 << 12);

	eLed.ledOn = (void *)ledOn;
}

int * ledOn (int * p) {
	*pGPFDAT = ~(1 << 4 | 1 << 5) ;

		return NULL;
}
