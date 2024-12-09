/*
 * gpio.c
 *
 *  Created on: Oct 19, 2024
 *      Author: elian
 */

#include <gpio.h>
#include <bits.h>
#include <fsl_gpio.h>
#include <fsl_port.h>
#include <pin_mux.h>
#include <MK64F12.h>

volatile static gpio_interrupt_flags_t g_intr_status_flag = {bit_0};

static void (*gpio_A_callback)(uint32_t flags) = bit_0;
static void (*gpio_B_callback)(uint32_t flags) = bit_0;
static void (*gpio_C_callback)(uint32_t flags) = bit_0;
static void (*gpio_D_callback)(uint32_t flags) = bit_0;

void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags)) {

	if(GPIO_A == gpio) {

		gpio_A_callback = handler;

	}
	else if(GPIO_B == gpio) {

		gpio_B_callback = handler;

	}
	else if(GPIO_C == gpio) {

		gpio_C_callback = handler;

	}
	else if(GPIO_D == gpio) {

		gpio_D_callback = handler;

	}

}

void GPIO_clear_irq_status(gpio_name_t gpio) {

	if(GPIO_A == gpio) {

		g_intr_status_flag.flag_port_a = false;

	}
	else if(GPIO_B == gpio) {

		g_intr_status_flag.flag_port_b = false;

	}
	else if(GPIO_C == gpio) {

		g_intr_status_flag.flag_port_c = false;

	}
	else if(GPIO_D == gpio) {

		g_intr_status_flag.flag_port_d = false;

	}

}

uint8_t GPIO_get_irq_status(gpio_name_t gpio) {

	uint8_t status = bit_0;

	if(GPIO_A == gpio) {

		status = g_intr_status_flag.flag_port_a;

	}
	else if(GPIO_B == gpio) {

		status = g_intr_status_flag.flag_port_b;

	}
	else if(GPIO_C == gpio) {

		status = g_intr_status_flag.flag_port_c;

	}
	else if(GPIO_D == gpio) {

		status = g_intr_status_flag.flag_port_d;

	}

	return(status);

}

void PORTA_IRQHandler(void) {

	uint32_t irq_status = bit_0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA);

	if(gpio_A_callback) {

		gpio_A_callback(irq_status);

	}

	GPIO_PortClearInterruptFlags(GPIOA, irq_status);

}

void PORTB_IRQHandler(void) {

	uint32_t irq_status = bit_0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOB);

	if(gpio_B_callback) {

		gpio_B_callback(irq_status);

	}

	GPIO_PortClearInterruptFlags(GPIOB, irq_status);

}

void PORTC_IRQHandler(void) {

	uint32_t irq_status = bit_0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOC);

	if(gpio_C_callback) {

		gpio_C_callback(irq_status);

	}

	GPIO_PortClearInterruptFlags(GPIOC, irq_status);

}

void PORTD_IRQHandler(void) {

	uint32_t irq_status = bit_0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOD);

	if(gpio_D_callback) {

		gpio_D_callback(irq_status);

	}

	GPIO_PortClearInterruptFlags(GPIOD, irq_status);

}

const gpio_pin_config_t gpio_input_config = {

		kGPIO_DigitalInput,
		bit_0,

};

const gpio_pin_config_t gpio_output_config = {

		kGPIO_DigitalOutput,
		bit_1,

};

const port_pin_config_t button_config = {

		kPORT_PullUp,					/* Internal pull-up resistor is enabled. */
		kPORT_FastSlewRate,				/* Fast slew rate is configured. */
		kPORT_PassiveFilterEnable,		/* Passive filter is enable. */
		kPORT_OpenDrainDisable,			/* Open drain is disabled. */
		kPORT_HighDriveStrength,		/* High drive strength is configured. */
		kPORT_MuxAsGpio,				/* Pin is configured as PTA4. */
		kPORT_UnlockRegister			/* Pin Control Register fields [15:0] are not locked. */

};

// Accelerometer.
const port_pin_config_t Accelerometer_config = {

		kPORT_PullUp,					/* Internal pull-up resistor is enabled. */
		kPORT_FastSlewRate,				/* Fast slew rate is configured. */
		kPORT_PassiveFilterDisable,		/* Passive filter is disabled. */
		kPORT_OpenDrainEnable,			/* Open drain is enable. */
		kPORT_LowDriveStrength,			/* Low drive strength is configured. */
		kPORT_MuxAlt5,					/* Pin is configured as SCL. */
		kPORT_UnlockRegister			/* Pin Control Register fields [15:0] are not locked. */

};

// SCL.
const port_pin_config_t SCL_config = {

		kPORT_PullUp,					/* Internal pull-up resistor is enabled. */
		kPORT_FastSlewRate,				/* Fast slew rate is configured. */
		kPORT_PassiveFilterDisable,		/* Passive filter is disabled. */
		kPORT_OpenDrainEnable,			/* Open drain is enable. */
		kPORT_LowDriveStrength,			/* Low drive strength is configured. */
		kPORT_MuxAlt2,					/* Pin is configured as SCL. */
		kPORT_UnlockRegister			/* Pin Control Register fields [15:0] are not locked. */

};

// SDA.
const port_pin_config_t SDA_config = {

		kPORT_PullUp,					/* Internal pull-up resistor is enabled. */
		kPORT_FastSlewRate,				/* Fast slew rate is configured. */
		kPORT_PassiveFilterDisable,		/* Passive filter is disabled. */
		kPORT_OpenDrainEnable,			/* Open drain is enable. */
		kPORT_LowDriveStrength,			/* Low drive strength is configured. */
		kPORT_MuxAlt2,					/* Pin is configured as SDA. */
		kPORT_UnlockRegister			/* Pin Control Register fields [15:0] are not locked. */

};

void GPIO_init(void) {

	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);

}

void LED_init(void) {

	// Red LED.
	PORT_SetPinMux(PORTB, bit_22, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, bit_22, &gpio_output_config);

	// Blue LED.
	PORT_SetPinMux(PORTB, bit_21, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOB, bit_21, &gpio_output_config);

	// Green LED.
	PORT_SetPinMux(PORTE, bit_26, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOE, bit_26, &gpio_output_config);

}

void SW_init(void) {

	// SW2.
	GPIO_PinInit(GPIOC, bit_6, &gpio_input_config);
	PORT_SetPinConfig(PORTC, bit_6, &button_config);
	PORT_SetPinInterruptConfig(PORTC, bit_6, kPORT_InterruptFallingEdge);

	// SW3.
	GPIO_PinInit(GPIOA, bit_4, &gpio_input_config);
	PORT_SetPinConfig(PORTA, bit_4, &button_config);
	PORT_SetPinInterruptConfig(PORTA, bit_4, kPORT_InterruptFallingEdge);

}

void Accelerometer_port_init(void) {

	// Configuración de GPIO para interrupciones del acelerómetro.
	PORT_SetPinMux(PORTC, bit_6, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, bit_6, &gpio_input_config);

	PORT_SetPinMux(PORTC, bit_13, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, bit_13, &gpio_input_config);

	// SCL.
	PORT_SetPinConfig(PORTE, bit_24, &Accelerometer_config);

	// SDA.
	PORT_SetPinConfig(PORTE, bit_25, &Accelerometer_config);

}

void I2C_port_init(void) {

	// SCL.
	PORT_SetPinConfig(PORTB, bit_2, &SCL_config);

	// SDA.
	PORT_SetPinConfig(PORTB, bit_3, &SDA_config);

	// SQW.
	GPIO_PinInit(GPIOD, bit_0, &gpio_input_config);
	PORT_SetPinConfig(PORTD, bit_0, &button_config);
	PORT_SetPinInterruptConfig(PORTD, bit_0, kPORT_InterruptFallingEdge);

	SIM->SOPT5 = ((SIM->SOPT5 & (~(SIM_SOPT5_UART0TXSRC_MASK))) | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));

}

void JOYSTICK_port_init(void) {

	// X axis.
	PORT_SetPinMux(PORTB, bit_2, kPORT_PinDisabledOrAnalog);

	// Y axis.
	PORT_SetPinMux(PORTB, bit_3, kPORT_PinDisabledOrAnalog);

	// Button.
	GPIO_PinInit(GPIOB, bit_10, &gpio_input_config);
	PORT_SetPinConfig(PORTB, bit_10, &button_config);
	PORT_SetPinInterruptConfig(PORTB, bit_10, kPORT_InterruptFallingEdge);

	SIM->SOPT5 = ((SIM->SOPT5 & (~(SIM_SOPT5_UART0TXSRC_MASK))) | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));

}

void UART0_port_init(void) {

	// UART0_RX.
	PORT_SetPinMux(PORTB, bit_16, kPORT_MuxAlt3);

	// UART0_TX.
	PORT_SetPinMux(PORTB, bit_17, kPORT_MuxAlt3);

}

void UART4_port_init(void) {

	// UART4_RX.
	PORT_SetPinMux(PORTC, bit_14, kPORT_MuxAlt3);

	// UART4_TX.
	PORT_SetPinMux(PORTC, bit_15, kPORT_MuxAlt3);

}
