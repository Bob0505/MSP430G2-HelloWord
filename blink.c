//***************************************************************************
//  Frist Example for MSP430 LaunchPad Blink LED
//
//  Description: Toggles P1.0 by xor'ing P1.0 inside of a software loop. This
//               example demonstrates the ease of starting a MSP430 project
//               that interacts with the outside via GPIO pins.
//
//                MSP430G2553
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//
//  gmaxsonic at gmail dot com
//**************************************************************************
#include <msp430g2553.h>

void main(void) {
	WDTCTL = WDTPW + WDTHOLD;	// disable watchdog

	P1OUT = 0x40;				// initialize LED off
	P1DIR = BIT0 | BIT6;		// P1.0 output

	while (1) {
		P1OUT ^= BIT0;				// Toggle LED on P1.0
		P1OUT ^= BIT6;				// Toggle LED on P1.6
		__delay_cycles(300000);	// Wait ~100ms at default DCO of ~1MHz
	}
} // main
