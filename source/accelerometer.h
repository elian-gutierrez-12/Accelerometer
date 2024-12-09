/*
 * accelerometer.h
 *
 *  Created on: Nov 16, 2024
 *      Author: elian
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdint.h>

#define FXOS8700CQ_ADDR  0x1D
#define REG_CTRL_REG1 	 0x2A
#define REG_XYZ_DATA_CFG 0x0E
#define REG_OUT_X_MSB 	 0x01

// Umbral para detección de movimiento.
#define THRESHOLD 		 1500

typedef enum {

	STATIONARY,
	UP,
	DOWN,
	RIGHT,
	LEFT

} Accelerometer_Position_t;

void Accelerometer_init(void);
void Accelerometer_read(int16_t *ax, int16_t *ay, int16_t *az);
uint8_t Accelerometer_position(void);

#endif /* ACCELEROMETER_H_ */
