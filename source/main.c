/*
 * main.c
 *
 *  Created on: Nov 16, 2024
 *      Author: elian
 */

#include <stdint.h>
#include <accelerometer.h>
#include <gpio.h>
#include <i2c.h>
#include <fsl_debug_console.h>

int main(void) {

	GPIO_init();
	Accelerometer_port_init();
	I2C_init();
	Accelerometer_init();

	PRINTF("Iniciando lectura del acelerómetro...\r\n");

	while(1) {

		int8_t position = Accelerometer_position();

		switch (position) {
			case UP:
				PRINTF("Position: Up\n");
				break;

			case DOWN:
				PRINTF("Position: Down\n");
				break;

			case RIGHT:
				PRINTF("Position: Right\n");
				break;

			case LEFT:
				PRINTF("Position: Left\n");
				break;

			case STATIONARY:
				PRINTF("Position: Stationary\n");
				break;

		}

		SDK_DelayAtLeastUs(150000, CLOCK_GetFreq(kCLOCK_CoreSysClk));

	}

}
