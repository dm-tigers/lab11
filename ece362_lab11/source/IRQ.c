/*----------------------------------------------------------------------------
 * Name:    IRQ.c
 * Purpose: IRQ Handler
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "LPC17xx.H"                         /* LPC17xx definitions           */
#include "LED1.h"
#include "ADC.h"

uint8_t  clock_1s;                           /* Flag activated each second    */


/*----------------------------------------------------------------------------
  Systick Interrupt Handler
  SysTick interrupt happens every 10 ms
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) {
  static uint8_t ticks = 0;
 
	/* Extra:
  if (ticks++ >= 99) {                       
    ticks    = 0;
    clock_1s = 1;
		if(LPC_GPIO1->FIOPIN & (1<<28)) 
		  {  
				LED1_Off();
			}
		else
		  {
		  LED1_On();
		  }
  }
*/
		
// 7. stop and start conversion
	ADC_StartCnv();
	ADC_StopCnv();
	
}
