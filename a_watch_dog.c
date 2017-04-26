#include "pub.h"

typedef struct {
	t_s3c2440_reg WTCON;//0x53000000^16
} S3C2440_WATCHDOG;

S3C2440_WATCHDOG * mWATCHDOG = (S3C2440_WATCHDOG * ) 0x53000000;

void disable_watchdog(void) {
	volatile unsigned short * pWTCON = (volatile unsigned short *)&mWATCHDOG->WTCON;

	*pWTCON = 0;
}
