/*
 * sleep.c
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#include "sleep.h"

volatile short is_delay=0;
volatile short is_sleep=0;
volatile int sleep_deadline=0;

void sleep_delay_us(long n)
{
	if(n<=62) return;
	is_delay=1;
	is_sleep=0;
	TACCTL0 = CCIE;
	TACCR0 = (long long)((double)n*ACLK_F/1000000.0-1);
	TACTL = TASSEL_1 + ID_0 + MC_1; //ACLK, DIV 0, Up.
	_EINT();
	LPM0;
}

void sleep_second(int n)
{
	if (n<=0) return;
	is_delay=0;
	is_sleep=1;
	sleep_deadline=n;
	TACCTL0 = CCIE;
	TACCR0 = ACLK_F-1;
	TACTL = TASSEL_1 + ID_0 + MC_1; //ACLK, DIV 0, Up.
	_EINT();
	LPM3;
}

#pragma vector = TIMERA0_VECTOR
__interrupt void sleep_TA_ISR(void)
{
	if (is_sleep)
	{
		--sleep_deadline;
		if(sleep_deadline<=0)
		{
			is_sleep=0;
			sleep_disableTA();
			LPM3_EXIT;
		}
	}
	else if (is_delay)
	{
		is_delay=0;
		sleep_disableTA();
		LPM0_EXIT;
	}
}


