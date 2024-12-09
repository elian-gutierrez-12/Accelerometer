/*
 * i2c.c
 *
 *  Created on: Nov 16, 2024
 *      Author: elian
 */

#include <i2c.h>
#include <clock_config.h>
#include <fsl_i2c.h>

i2c_master_handle_t g_m_handle;
volatile bool completionFlag = false;

// Callback de I2C.
static void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData) {

	if (status == kStatus_Success) {

		completionFlag = true;

	}

}

// Inicialización del I2C.
void I2C_init(void) {

	i2c_master_config_t masterConfig;
	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUDRATE;
	I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));
	I2C_MasterTransferCreateHandle(I2C0, &g_m_handle, i2c_master_callback, NULL);

}

// Escritura en un registro.
void I2C_WriteRegister(uint8_t slaveAddress, uint8_t reg, uint8_t value) {

	uint8_t data[2] = {reg, value};
	i2c_master_transfer_t masterXfer = {
			.slaveAddress 	= slaveAddress,
			.direction 		= kI2C_Write,
			.subaddress 	= 0,
			.subaddressSize = 0,
			.data 			= data,
			.dataSize 		= 2,
			.flags 			= kI2C_TransferDefaultFlag,
	};
	I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);
	while(!completionFlag) {}
	completionFlag = false;

}

// Lectura de registros.
void I2C_ReadRegisters(uint8_t slaveAddress, uint8_t reg, uint8_t *buffer, size_t size) {

	i2c_master_transfer_t masterXfer = {
			.slaveAddress 	= slaveAddress,
			.direction 		= kI2C_Read,
			.subaddress 	= reg,
			.subaddressSize = 1,
			.data 			= buffer,
			.dataSize 		= size,
			.flags 			= kI2C_TransferDefaultFlag,
	};
	I2C_MasterTransferNonBlocking(I2C0, &g_m_handle, &masterXfer);
	while(!completionFlag) {}
	completionFlag = false;

}
