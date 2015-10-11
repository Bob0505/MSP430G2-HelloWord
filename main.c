#include <msp430.h>
#include <msp430g2553.h>
#include "main.h"

void FunSelGPIO(
	uint8_t		selectedPort,
	uint8_t		selectedPins
){
	//8.2.5 Function Select Registers PxSEL and PxSEL2
	//PxSEL2  PxSEL
	//	0 		0	I/O function is selected
	switch (selectedPort)
	{
		case GPIO_Port1:
			P1SEL	&= ~selectedPins;
			P1SEL2	&= ~selectedPins;
			break;

		case GPIO_Port2:
			break;

		default:
			break;
	}
	return;
}

void GPIO_SetOutput(
	uint8_t			selectedPort,
	uint8_t			selectedPins,
	GPIO_SETTING	*gpiosettings
){
	FunSelGPIO(selectedPort, selectedPins);

	switch (selectedPort)
	{
		case GPIO_Port1:
			P1DIR |=  selectedPins;
			if(GPIO_Low == gpiosettings->r.output)
				P1OUT &= ~selectedPins;
			else // GPIO_High
				P1OUT |=  selectedPins;
			break;

		case GPIO_Port2:
			break;

		default:
			break;
	}
	return;
}

void GPIO_SetInput(
	uint8_t			selectedPort,
	uint8_t			selectedPins,
	GPIO_SETTING	*gpiosettings
){
	FunSelGPIO(selectedPort, selectedPins);

	P1DIR &= ~selectedPins;

	//8.2.4 Pullup/Pulldown Resistor Enable Registers PxREN
	if(Disable == gpiosettings->r.pullren)
	{
		P1REN &= ~selectedPins;
	} else	{	// Enable
		P1REN |=  selectedPins;

		if(GPI_PullDown == gpiosettings->r.output)
			P1OUT &= ~selectedPins;
		else	//GPI_PullUp
			P1OUT |= selectedPins;
	}

	if(Disable == gpiosettings->r.intr_en)
	{
		P1IE &= ~selectedPins;
	} else {	// Enable
		P1IE |= selectedPins;

		if(GPI_intr_Rising == gpiosettings->r.intr_es)
			P1IES &= ~selectedPins;
		else	// GPI_intr_Falling
			P1IES |= selectedPins;

		P1IFG &= ~selectedPins;			// P1.3 IFG cleared
	}
	return;
}


//P1.0	Red LED
//P1.3	Button
//P1.6	Green LED

int main(void) {

	GPIO_SETTING	gpiosettings;

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
#if	0
	// initialize P1.0 output Low and P1.6 output High
	gpiosettings.r.Direction= GPIO_Output;
	gpiosettings.r.output	= GPIO_Low;
    GPIO_SetOutput( GPIO_Port1, BIT0, &gpiosettings);
	gpiosettings.r.output	= GPIO_High;
    GPIO_SetOutput( GPIO_Port1, BIT6, &gpiosettings);

	while (1) {
		P1OUT ^= BIT0;				// Toggle LED on P1.0
		P1OUT ^= BIT6;				// Toggle LED on P1.6
		__delay_cycles(100000);		// Wait ~100ms at default DCO of ~1MHz
	}
}
#else
	CCTL0 = CCIE;					// CCR0 interrupt enabled
	//12.3.1 TACTL, Timer_A Control Register
	TACTL = TASSEL_2 | ID_3 | MC_1;	// SMCLK, /8, Up mode
	CCR0 =  10000;					// 12.5 Hz

	// Shut down everything
	P1OUT &= 0x00;
	P1DIR &= 0x00;

	// initialize P1.0 and P1.6 pins output Low the rest are input
	gpiosettings.r.Direction= GPIO_Output;
	gpiosettings.r.output	= GPIO_Low;
    GPIO_SetOutput( GPIO_Port1, BIT0, &gpiosettings);
    GPIO_SetOutput( GPIO_Port1, BIT6, &gpiosettings);

	// initialize P1.3 pin input PullUp Falling trigger
	gpiosettings.r.Direction= GPIO_Input;
    gpiosettings.r.pullren	= Enable;
    gpiosettings.r.output	= GPI_PullUp;
    gpiosettings.r.intr_en	= Enable;
    gpiosettings.r.intr_es	= GPI_intr_Falling;
    GPIO_SetInput( GPIO_Port1, BIT3, &gpiosettings);

	// Enter LPM0 w/ interrupt
	_BIS_SR(CPUOFF + GIE);

//	while(1){}	//Loop forever, we work with interrupts!
	return 0;
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= BIT0;	// Toggle P1.0
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	P1OUT ^= BIT6;	// Toggle P1.6
	P1IFG &= ~BIT3;	// P1.3 IFG cleared
}
#endif
