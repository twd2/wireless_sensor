/*
 * sleep.c
 *
 *  Created on: 2013-12-31
 *      Author: twd2
 */

#include <msp430.h> 
#include "sleep.h"
#include "i2c.h"
#include "sht2x.h"
#include "RCSwitch.h"
#include "serial.h"
#include "utils.h"


#include "config.h"

void setclk()
{
    BCSCTL1 |= DIVA_0+RSEL2+RSEL1+RSEL0; //DIVA /1, max RSEL
    BCSCTL1 &=~XTS;
    DCOCTL=DCO1+DCO0+DCO2; //max DCO
}

void init()
{
	utils_killdog();
	sleep_disableTA();
	setclk();
	P1DIR=0xFF;
	P1OUT=0x00;
	P2DIR=0xFF;
	P2OUT=0x00;
	P3DIR=0xFF;
	P3OUT=0x00;
	P4DIR=0xFF;
	P4OUT=0x00;
	P5DIR=0xFF;
	P5OUT=0x00;
	P6DIR=0xFF;
	P6OUT=0x00;
}

unsigned long mkpkg(unsigned long type, unsigned long value)
{
	return ( ((CFG_ADDRESS<<24) & CFG_ADDR_MASK) | (type & CFG_TYPE_MASK) | (value & CFG_VALUE_MASK) );
}

void tostr(int n,char *buff, unsigned int count)
{
	if (n<0) n=-n;
	unsigned int i;
	for(i=count;i!=0;--i)
	{
		buff[i-1]=(n%10)+'0';
		n/=10;
	}
	buff[count]='\0';
}

void test_serial()
{
	serial_write_str("hello, world\r\n");
	for(;;)
	{
		serial_write_byte(serial_read_byte());
	}
}

void test_sht2x()
{
	static char buf[10];
	for(;;)
	{
		float tmp=sht2x_temp();
		tostr(tmp,buf,2);
		serial_write_str(buf);
		serial_write_str(".");
		tostr((int)(tmp*100)%100,buf,2);
		serial_write_str(buf);
		serial_write_str("C ");
		tmp=sht2x_rh();
		tostr(tmp,buf,2);
		serial_write_str(buf);
		serial_write_str(".");
		tostr((int)(tmp*100)%100,buf,2);
		serial_write_str(buf);
		serial_write_str("%\r\n");
		//sleep_second(1);
	}
}

void main()
{
	init();

	serial_init();

	test_sht2x();

    for(;;)
    {
    	long tmp,pkg;
    	tmp=sht2x_temp_raw();
    	pkg=mkpkg(CFG_TYPE_Temperature, tmp);
    	rc_init();
    	rc_sync();
    	REPEAT(i,4)
    	{
    		rc_send(pkg, 32);
    		rc_sync();
    	}
    	tmp=sht2x_rh_raw();
    	pkg=mkpkg(CFG_TYPE_Humidity, tmp);
    	rc_init();
    	rc_sync();
    	REPEAT(j,4)
    	{
    		rc_send(pkg, 32);
    		rc_sync();
    	}
#ifndef DEBUG_
		sleep_second(CFG_SnoozingTimeS);
#else
		sleep_second(1);
#endif
    }
    //return 0;
}
