/*
 * RCSwitch.c
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#include "RCSwitch.h"

void rc_init()
{
	P2DIR |= RC_TXPIN;
	RC_DATA_0;
	utils_delay_us(pulseLength*1);
}

void rc_send_bit(unsigned char x)
{
	if (x)
	{
		RC_DATA_1;
		utils_delay_us(pulseLength*3);
		RC_DATA_0;
		utils_delay_us(pulseLength*1);
	}
	else
	{
		RC_DATA_1;
		utils_delay_us(pulseLength*1);
		RC_DATA_0;
		utils_delay_us(pulseLength*3);
	}
}

void rc_send(unsigned long x, unsigned int n)
{
	if (n>32) return;
	int i;
	for(i=n;i!=0;--i)
	{
		rc_send_bit((x>>(n-1))&1); //MSBдкЧА
		x<<=1;
	}
}

void rc_sync()
{
	RC_DATA_1;
	utils_delay_us(pulseLength*1);
	RC_DATA_0;
	utils_delay_us(pulseLength*31);
}
