/*
 * serial.c
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#include "serial.h"

volatile int rx;

void serial_init()
{
	//baud = 9600
	P3DIR &= ~0x20;
	P3SEL |= 0x30; // P3.4 P3.5 = USART0 TXD/RXD
	U0ME=URXE0+UTXE0; // Enable USART0 TXD/RXD
	U0CTL |= CHAR; //8bit
	U0TCTL = SSEL0; //ACLK
	U0BR0 = 0x03; // 32768/9600 = 3.41
	U0BR1 = 0x00; //
	U0MCTL = 0x4A;// Modulation
	U0CTL &= ~SWRST;// Initialize USART state machine
	IE1 |= URXIE0 + UTXIE0;
	_EINT();
}

void serial_write_byte(unsigned char b)
{
	_EINT();
	U0TXBUF=b;
	//unsigned int i=0;
	//while (!(IFG1 & UTXIFG0) && (++i<500));
	LPM0;
	//IFG1 &= ~UTXIFG0;
}

void serial_write(unsigned char *buff, unsigned int count)
{
	unsigned int i;
	for(i=0;i<count;++i)
	{
		serial_write_byte(buff[i]);
	}
}

void serial_write_str(char *buff)
{
	while(*buff != '\0')
	{
		serial_write_byte(*buff);
		++buff;
	}
}


void serial_write_async(unsigned char *buff, unsigned int count)
{
	//Not implemented
}

void serial_write_byte_async(unsigned char b)
{
	//Not implemented
}

unsigned char serial_read_byte()
{
	_EINT();
	if (rx==-1)
	{
		LPM0;
	}
	//while (rx==-1);
	unsigned char data;
	data=rx;
	rx=-1;
	return data;
}

int serial_peek()
{
	return rx;
}

int serial_available()
{
	return rx>=0;
}

#pragma vector=USART0TX_VECTOR
__interrupt void serial_USART0TX_ISR()
{
	LPM0_EXIT;
}

#pragma vector=USART0RX_VECTOR
__interrupt void serial_USART0RX_ISR()
{
	rx=U0RXBUF;
	LPM0_EXIT;
}
