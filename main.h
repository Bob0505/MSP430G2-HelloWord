/*
 * main.h
 *
 *  Created on: 2015¦~9¤ë30¤é
 *      Author: Bob3
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

//Table 8-2. Digital I/O Registers
typedef union {
	uint8_t	ul;
	struct {
		uint8_t	input	: 1;	// 0	input value
		uint8_t	output	: 1;	// 1	input pulldir/output value
		uint8_t	Direction:1;	// 2	input/output direction
		uint8_t	intr_ifg: 1;	// 3	interrupt flag
		uint8_t	intr_es	: 1;	// 4	interrupt edge select registers
		uint8_t	intr_en	: 1;	// 5	interrupt enable
		uint8_t	pullren	: 1;	// 6	input Pullup/pulldown resistor enable
		uint8_t	reserve : 1;	// 7
  } r;
} GPIO_SETTING;

enum MSP430_STATUS
{
	Status_Success = 0x00
};

enum MSP430_EnDis
{
	Disable = 0x00,
	Enable	= 0x01
};

enum MSP430_GPIO_PORT
{
	GPIO_Port1 = 0x01,
	GPIO_Port2 = 0x02
};

//8.2.2 Output Registers PxOUT
//	Bit = 0: The output is low
//	Bit = 1: The output is high
enum MSP430_GPIO_VALUE
{
	GPIO_Low	= 0x00,
	GPIO_High	= 0x01
};

enum MSP430_GPI_PULLDIR
{
	GPI_PullDown= 0x00,
	GPI_PullUp	= 0x01
};

//8.2.3 Direction Registers PxDIR
//	Bit = 0: The port pin is switched to input direction
//	Bit = 1: The port pin is switched to output direction
enum MSP430_GPIO_DIR
{
	GPIO_Input	= 0x00,
	GPIO_Output	= 0x01
};

enum MSP430_GPI_INTR_ES
{
	GPI_intr_Rising	= 0x00,
	GPI_intr_Falling= 0x01
};

#endif /* MAIN_H_ */
