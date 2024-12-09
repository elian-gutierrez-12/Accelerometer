/*
 * i2c.h
 *
 *  Created on: Nov 16, 2024
 *      Author: elian
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#define I2C_BAUDRATE 100000U

void I2C_init(void);
void I2C_WriteRegister(uint8_t slaveAddress, uint8_t reg, uint8_t value);
void I2C_ReadRegisters(uint8_t slaveAddress, uint8_t reg, uint8_t *buffer, size_t size);

#endif /* I2C_H_ */
