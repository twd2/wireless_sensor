/*
 * sht2x.c
 *
 *  Created on: 2014-1-4
 *      Author: twd2
 */

#include "sht2x.h"

unsigned long sht2x_read(unsigned char cmd)
{
	i2c_init();
	unsigned char rbuff[2];
	i2c_write_byte(SHT2x_ADDR,cmd);
	i2c_read_data(0x40,rbuff,2);
	return 0x100*(unsigned long)(rbuff[0]) + (unsigned long)(rbuff[1]);
}

unsigned long sht2x_temp_raw()
{
	return sht2x_read(SHT2x_CMD_TEMP);
}

float sht2x_temp()
{
	return 175.72f*(float)(sht2x_temp_raw())/65536.0f - 46.85f;
}

unsigned long sht2x_rh_raw()
{
	return sht2x_read(SHT2x_CMD_RH);
}

float sht2x_rh()
{
	return 125.0f*(float)(sht2x_rh_raw())/65536.0f - 6.0f;
}
