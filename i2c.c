/*
 * i2c.c
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#include "i2c.h"

void i2c_init()
{
	SCL_OUT;
	SDA_IN;
	SCL_0;
	i2c_stop();
}

void i2c_start()
{
	SDA_OUT;
	SCL_OUT;
	SDA_1;
	utils_delay_us(5);
	SCL_1;
	utils_delay_us(5);
	SDA_0;
	utils_delay_us(5);
	SCL_0;
	utils_delay_us(5);
}

void i2c_stop()
{
	SDA_OUT;
	SCL_OUT;
	SCL_0;
	utils_delay_us(5);
	SDA_0;
	utils_delay_us(5);
	SCL_1;
	utils_delay_us(5);
	SDA_1;
	utils_delay_us(5);
}

void i2c_ack()
{
	SDA_OUT;
	SCL_OUT;
	SDA_0;
	utils_delay_us(5);
	SCL_1;
	utils_delay_us(5);
	SCL_0;
	utils_delay_us(5);
	SDA_1;
}

void i2c_nack()
{
	SDA_OUT;
	SCL_OUT;
	SDA_1;
	utils_delay_us(5);
	SCL_1;
	utils_delay_us(5);
	SCL_0;
	utils_delay_us(5);
}

unsigned char i2c_test_ack()
{
	unsigned char tmp;
	SDA_IN;
	SCL_OUT;
	utils_delay_us(5);
	SCL_1;
	utils_delay_us(5);
	tmp = SDA_BIT_DATA;
	utils_delay_us(5);
	SCL_0;
	utils_delay_us(5);
	return tmp;
}

void i2c_write(unsigned char data)
{
	SDA_OUT;
	SCL_OUT;
	unsigned char i;
	for(i=8;i!=0;--i)
	{
		SDA_OUT;
		if(data>>7)
			SDA_1;
		else
			SDA_0;
		utils_delay_us(10);
		SCL_1;
		utils_delay_us(5);
		SCL_0;
		utils_delay_us(10);
		data=data<<1;
	}
	SDA_IN;
	utils_delay_us(5);
}

unsigned char i2c_read()
{
	unsigned char byte = 0;
	SDA_IN;
	SCL_1;
	SCL_OUT;
	unsigned char i;
	for(i=8;i!=0;--i)
	{
		SCL_1;
		utils_delay_us(10);
		byte <<= 1;
		byte |= SDA_BIT_DATA;
		utils_delay_us(10);
		SCL_0;
		utils_delay_us(10);
	}
	return byte;
}

unsigned char i2c_write_data(unsigned char addr, unsigned char *buff, unsigned char count)
{
	i2c_start();
	i2c_write(0x0|(addr<<1)); //ADDRESS+W
	if(i2c_test_ack() != 0)
		return 1;
	unsigned char i=0;
	for(i=0;i<count;++i)
	{
		i2c_write(buff[i]);
		if(i2c_test_ack() != 0)
			return 1;
	}
	i2c_stop();
	return 0;
}

unsigned char i2c_read_data(unsigned char addr, unsigned char *buff, unsigned char count)
{
	unsigned char i;
	i2c_start();
	i2c_write(0x1|(addr<<1)); //ADDRESS+R
	if(i2c_test_ack() != 0)
		return 1;
	SCL_IN;
	while(!SCL_BIT_DATA); //wait for the slave to release the SCL
	for(i=0;i<count-1;++i)
	{
		buff[i] = i2c_read();
		i2c_ack();
	}
	buff[count-1] = i2c_read();
	i2c_nack();
	i2c_stop();
	return 0;
}

unsigned char i2c_write_byte(unsigned char addr, unsigned char data)
{
	unsigned char buff[1];
	buff[0]=data;
	return i2c_write_data(addr, buff, 1);
}

int i2c_read_byte(unsigned char addr)
{
	unsigned char buff[1];
	unsigned char r=i2c_read_data(addr, buff, 1);
	if (r) return -1;
	return buff[0];
}
