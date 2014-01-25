/*
 * config.h
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define DEBUG_

#define CFG_ADDRESS         19L
#define CFG_SnoozingTimeS   60L

#define CFG_ADDR_MASK  0xFF000000L //0b11111111000000000000000000000000L
#define CFG_TYPE_MASK  0x00FF0000L //0b00000000111111110000000000000000L
#define CFG_VALUE_MASK 0x0000FFFFL //0b00000000000000001111111111111111L

#define CFG_TYPE_Humidity     (0x5EL<<16) //(0b01011110L<<16)
#define CFG_TYPE_Temperature  (0x5FL<<16) //(0b01011111L<<16)
#define CFG_TYPE_Distance     (0x60L<<16) //(0b01100000L<<16)
#define CFG_TYPE_Illumination (0x61L<<16) //(0b01100001L<<16)

//It doesn't support 0bxxxx?! >_< :<

#endif /* CONFIG_H_ */
