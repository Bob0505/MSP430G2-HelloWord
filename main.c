#include <msp430.h>
#include <msp430g2553.h>
#include "main.h"

int GPIORW(
	uint8_t selectedPort,
	uint8_t selectedPins,
	uint8_t DIR_InOut,
	uint8_t HL
){
	uint8_t status = Status_Success;

	switch (selectedPort)
	{
		case GPIO_Port1:
			if(GPIO_Input == DIR_InOut)
			{
				P1DIR &= ~selectedPins;
			}
			else if(GPIO_Output == DIR_InOut)
			{
				P1DIR |=  selectedPins;
				//init GPO High/Low
				//8.2.2 Output Registers PxOUT
				//	Bit = 0: The output is low
				//	Bit = 1: The output is high
				if(GPO_Low == HL)
					P1OUT &= ~selectedPins;
				else if(GPO_High == HL)
					P1OUT |=  selectedPins;
			}
			break;
		case GPIO_Port2:

			break;
		default:

			break;
	}

	return status;
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    GPIORW( GPIO_Port1, BIT0, GPIO_Output, GPO_Low);	// initialize P1.0 output Low
    GPIORW( GPIO_Port1, BIT6, GPIO_Output, GPO_High);	// initialize P1.6 output High

	while (1) {
		P1OUT ^= BIT0;				// Toggle LED on P1.0
		P1OUT ^= BIT6;				// Toggle LED on P1.6
		__delay_cycles(100000);		// Wait ~100ms at default DCO of ~1MHz
	}


	return 0;
}
