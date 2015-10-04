/*
 * main.h
 *
 *  Created on: 2015¦~9¤ë30¤é
 *      Author: Bob3
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef unsigned char uint8_t ;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

enum MSP430_STATUS
{
	Status_Success = 0x00
};

enum MSP430_GPIO_PORT
{
	GPIO_Port1 = 0x01,
	GPIO_Port2 = 0x02
};

enum MSP430_GPIO_DIR
{
	GPIO_Input	= 0x00,
	GPIO_Output	= 0x01
};

enum MSP430_GPO_HL
{
	GPO_Low	 = 0x00,
	GPO_High = 0x01
};

#endif /* MAIN_H_ */
