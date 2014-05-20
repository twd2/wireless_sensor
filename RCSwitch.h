/*
 * RCSwitch.h
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#ifndef RCSWITCH_H_
#define RCSWITCH_H_

#include "utils.h"

#define RC_TXPIN  BIT3
#define RC_DATA_1 (P2OUT |= RC_TXPIN)
#define RC_DATA_0 (P2OUT &= ~RC_TXPIN)

#define pulseLength 350 //us

void rc_init();
void rc_send_bit(unsigned char);
void rc_send(unsigned long, unsigned int);
void rc_sync();

#endif /* RCSWITCH_H_ */
