/*
 * utils.h
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <msp430.h>

#define REPEAT(k,n) unsigned int k;for(k=n;k!=0;--k)
#define CPU_F ((double)8000000)
#define utils_delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define utils_delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

void utils_killdog();

#endif /* UTILS_H_ */
