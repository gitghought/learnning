#include "my_nand.h"

static S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

void s3c2440_my_nand_reset (void) {
	s3c2440_my_nand_select_chip();

	s3c2440_my_nand_write_command(0xff);

	s3c2440_my_nand_is_busy();
	s3c2440_my_nand_disselect_chip();
}

unsigned char s3c2440_my_nand_read_data(void) {
	volatile unsigned char * p = (volatile unsigned char *)&s3c2440nand->NFDATA;
	return (*p);
}

void s3c2440_my_nand_write_address (unsigned int addr) {
	int i;
	volatile unsigned char *p = (volatile unsigned char * )&s3c2440nand->NFADDR;
	unsigned int col = addr & 0x7ff;
	unsigned int page = (addr >> 11) & 0xffff;

	*p = col & 0xff;			/* Column Address A0~A7 */
	for(i=0; i<10; i++);		
	*p = (col >> 8) & 0x0f; 	/* Column Address A8~A11 */
	for(i=0; i<10; i++);
	*p = page & 0xff;			/* Row Address A12~A19 */
	for(i=0; i<10; i++);
	*p = (page >> 8) & 0xff;	/* Row Address A20~A27 */
	for(i=0; i<10; i++);
	*p = (page >> 16) & 0x01;	/* Row Address A28~A29 */
	for(i=0; i<10; i++);
}

void s3c2440_my_nand_write_command(int cmd) {
	volatile unsigned char * pnfcmd = (volatile unsigned char *)&s3c2440nand->NFCMD;
	*pnfcmd = cmd;

}

void s3c2440_my_nand_is_busy (void) {
	unsigned char val = 0;
	int i = 0;
	volatile unsigned char * pNFSTAT = (volatile unsigned char *) (&(s3c2440nand->NFSTAT));

	while (1) {
		val = (*pNFSTAT) & (1 << 0);
		if (val == 0) {
			for (i = 0; i < 10; i++) {
				;
			}
		} else if (val > 0) {
			break;
		}
	}
}

void s3c2440_my_nand_disselect_chip (void) {
	s3c2440nand->NFCONT |= 1 << 0;
	s3c2440nand->NFCONT |= (1 << 1);
}

void s3c2440_my_nand_select_chip (void) {
	s3c2440nand->NFCONT |= 1 << 0;
	s3c2440nand->NFCONT &= ~(1 << 1);
}

void s3c2440_my_namd_init(void) {
        s3c2440nand->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
        /* Ê¹ÄÜNAND Flash¿ØÖÆÆ÷, ³õÊ¼»¯ECC, ½ûÖ¹Æ¬Ñ¡ */
        s3c2440nand->NFCONT = (1<<4)|(1<<1)|(1<<0);
}
