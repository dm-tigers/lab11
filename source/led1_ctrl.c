

#include "LPC17xx.H"                         /* LPC17xx definitions           */
#include "LED1.h"

/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED1_Init (void) {

  LPC_SC->PCONP   |= (1<<15);
	
	LPC_GPIO1->FIODIR |=  0xB0000000;  // 1101 port 1, Pin: 31, 30, 28: output
}

/*----------------------------------------------------------------------------
  Function that turns on requested LED 1
 *----------------------------------------------------------------------------*/
void LED1_On () {

	LPC_GPIO1->FIOPIN |= (1<<28);
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED1_Off () {

  LPC_GPIO1->FIOPIN &= ~(1<<28);
}

