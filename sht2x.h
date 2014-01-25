/*
 * sht2x.h
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#ifndef SHT2X_H_
#define SHT2X_H_

#include "i2c.h"

#define SHT2x_ADDR 0x40
#define SHT2x_CMD_TEMP 0xE3
#define SHT2x_CMD_RH 0xE5

unsigned long sht2x_read(unsigned char);
unsigned long sht2x_temp_raw();
float sht2x_temp();
unsigned long sht2x_rh_raw();
float sht2x_rh();

#endif /* SHT2X_H_ */
