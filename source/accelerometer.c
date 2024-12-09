/*
 * accelerometer.c
 *
 *  Created on: Nov 16, 2024
 *      Author: elian
 */

#include <accelerometer.h>
#include <i2c.h>

void Accelerometer_init(void) {

	// Configurar el acelerómetro en modo standby.
	I2C_WriteRegister(FXOS8700CQ_ADDR, REG_CTRL_REG1, 	 0x00);
	// Configurar el rango del acelerómetro a ±2g.
	I2C_WriteRegister(FXOS8700CQ_ADDR, REG_XYZ_DATA_CFG, 0x00);
	// Activar el acelerómetro.
	I2C_WriteRegister(FXOS8700CQ_ADDR, REG_CTRL_REG1, 	 0x01);

}

void Accelerometer_read(int16_t *ax, int16_t *ay, int16_t *az) {

	uint8_t data[6];
	I2C_ReadRegisters(FXOS8700CQ_ADDR, REG_OUT_X_MSB, data, 6);

	// Convertir datos de 16 bits con formato específico del sensor.
	*ax = ((int16_t)((data[0] << 8) | data[1])) >> 2;
	*ay = ((int16_t)((data[2] << 8) | data[3])) >> 2;
	*az = ((int16_t)((data[4] << 8) | data[5])) >> 2;

}

uint8_t Accelerometer_position(void) {

	int16_t ax, ay, az;
	Accelerometer_read(&ax, &ay, &az); // Leer los valores del acelerómetro.

	if(ax < -THRESHOLD) {

		return UP;

	}
	else if(ax > THRESHOLD) {

		return DOWN;

	}
	else if(ay > THRESHOLD) {

		return RIGHT;

	}
	else if(ay < -THRESHOLD) {

		return LEFT;

	}
	else {

		return STATIONARY;

	}

}
