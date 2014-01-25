/*
 * sleep.h
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#ifndef SLEEP_H_
#define SLEEP_H_

#include <msp430.h>

#define ACLK_F 32768

void sleep_delay_us(long);

#define sleep_disableTA() \
{ \
	TACCTL0 &= ~CCIE; \
	TACTL = MC_0 + TACLR; \
}
void sleep_second(int);
__interrupt void sleep_TA_ISR(void);

#endif /* SLEEP_H_ */
