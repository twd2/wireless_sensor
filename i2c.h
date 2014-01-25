/*
 * i2c.h
 *
 *  Created on: 2014-1-1
 *      Author: twd2
 */

#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>

#include "utils.h"

#define SDA_BIT   BIT1
#define SCL_BIT   BIT2
#define IIC_PORT_DIR P2DIR
#define IIC_PORT_DATA P2OUT
#define SDA_BIT_DATA  ((P2IN & SDA_BIT)==SDA_BIT)
#define SCL_BIT_DATA  ((P2IN & SCL_BIT)==SCL_BIT)

#define SDA_OUT  (IIC_PORT_DIR |= SDA_BIT)
#define SDA_IN    (IIC_PORT_DIR &= ~SDA_BIT)
#define SDA_1     (IIC_PORT_DATA |= SDA_BIT)
#define SDA_0     (IIC_PORT_DATA &= ~SDA_BIT)

#define SCL_IN    (IIC_PORT_DIR &= ~SCL_BIT)
#define SCL_OUT  (IIC_PORT_DIR |= SCL_BIT)
#define SCL_1     (IIC_PORT_DATA |= SCL_BIT)
#define SCL_0     (IIC_PORT_DATA &= ~SCL_BIT)

void i2c_init();
void i2c_start();
void i2c_stop();
void i2c_ack();
void i2c_nack();
unsigned char i2c_test_ack();
void i2c_write(unsigned char);
unsigned char i2c_read();
unsigned char i2c_write_data(unsigned char, unsigned char*, unsigned char);
unsigned char i2c_read_data(unsigned char, unsigned char*, unsigned char);
unsigned char i2c_write_byte(unsigned char, unsigned char);
int i2c_read_byte(unsigned char);

#endif /* I2C_H_ */
