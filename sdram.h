#ifndef SDRAM_H
#define SDRAM_H

#include "pub.h"

typedef struct {
	t_s3c2440_reg BWSCON;
	t_s3c2440_reg BANKCON0 ;
	t_s3c2440_reg BANKCON1 ;
	t_s3c2440_reg BANKCON2 ;
	t_s3c2440_reg BANKCON3 ;
	t_s3c2440_reg BANKCON4 ;
	t_s3c2440_reg BANKCON5 ;
	t_s3c2440_reg BANKCON6 ;
	t_s3c2440_reg BANKCON7 ;
	t_s3c2440_reg REFRESH ;
	t_s3c2440_reg BANKSIZE ;
	t_s3c2440_reg MRSRB6 ;
	t_s3c2440_reg MRSRB7 ;
}S3C2440_SDRAM;

#endif
