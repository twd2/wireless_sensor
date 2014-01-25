/*
 * serial.h
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <msp430.h>
#include "utils.h"

void serial_init();
void serial_write_byte(unsigned char);
void serial_write(unsigned char *, unsigned int);
void serial_write_str(char *);
void serial_write_async(unsigned char *, unsigned int);
void serial_write_byte_async(unsigned char);
unsigned char serial_read_byte();
int serial_peek();
int serial_available();
__interrupt void serial_USART0TX_ISR();
__interrupt void serial_USART0RX_ISR();



#endif /* SERIAL_H_ */
