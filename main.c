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
    //BCSCTL1 |= DIVS_0 + DIVM_0 + DIVA_0 + RSEL2 + RSEL1 + RSEL0; //DIVA /1, max RSEL
	//DCOCTL=DCO1+DCO0+DCO2; //max DCO

	BCSCTL1 |= DIVS_0 + DIVM_0 + DIVA_0; //DIVA,S,M /1, RSEL: default
	//BCSCTL1 |= DIVS_0 + DIVM_0 + DIVA_3; //DIVA,S,M /1, RSEL: default
	BCSCTL1 &= ~XTS; //LFXTCLK Low Frequency

    BCSCTL1 &= ~XT2OFF; //power on XT2
    do
    {
    	IFG1 &= ~OFIFG; //clear oscillator fault
    	unsigned int i;
    	for (i = 0xFF; i != 0; i--);
    }
    while ((IFG1 & OFIFG)); //oscillator fault

    BCSCTL2 |= SELM_2; //MCLK: XT2CLK
    BCSCTL2 |= SELS; //SMCLK: XT2CLK
}

void init()
{
	utils_killdog();
	sleep_disableTA();
	setclk();

	//pull down IO ports
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
		sleep_second(1);
	}
}

void main()
{
	init();

#ifdef DEBUG_
	serial_init();
#endif

	//test_sht2x();

	/*for(;;)
	{
		P2OUT = 0x00;
		utils_delay_us(100);
		P2OUT = 0xFF;
		utils_delay_us(100);
	}*/

	/*rc_init();
	rc_sync();
	rc_send(0xFFFFFFFF, 32);*/
	for(;;)
    {
    	//P3OUT|=BIT0;
    	long tmp, pkg;
    	tmp=sht2x_temp()*100;
    	pkg=mkpkg(CFG_TYPE_Temperature, tmp);
    	rc_init();
    	rc_sync();
    	REPEAT(i,8)
    	{
    		rc_send(pkg, 32);
    		rc_sync();
    	}
    	tmp=sht2x_rh()*100;
    	pkg=mkpkg(CFG_TYPE_Humidity, tmp);
    	rc_init();
    	rc_sync();
    	REPEAT(j,8)
    	{
    		rc_send(pkg, 32);
    		rc_sync();
    	}
    	//P3OUT &=~BIT0;
#ifndef DEBUG_
		sleep_second(CFG_SnoozingTimeS);
#else
		sleep_second(1);
#endif
    }
    //return 0;
}
