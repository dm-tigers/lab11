/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s): possible defines set in "options for target - C/C++ - Define"
 *            __USE_LCD   - enable Output on LCD
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "LPC17xx.H"                         /* LPC17xx definitions           */
#include "GLCD.h"
#include "Serial.h"
#include "LED1.h"
#include "ADC.h"

#define __FI        1                       /* Font index 16x24               */

char text[10];

/* Import external variables from IRQ.c file                                  */
extern uint8_t  clock_1s;

#define __USE_LCD
//#define ADC_DONE (LPC_ADC->ADGDR >> 31)

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) 
{
  	uint16_t ad_avg = 0, ad_avg_count = 0;
  	uint16_t ad_val = 0, ad_val_old = 0xFFFF;

	LED1_Init();                                /* LED Initialization            */
  	SER_Init();                                /* UART Initialization           */
  	ADC_Init();                                /* ADC Initialization            */

#ifdef __USE_LCD
	GLCD_Init();                               /* Initialize graphical LCD      */
  	GLCD_Clear(White);                         /* Clear graphical LCD display   */
  	GLCD_SetBackColor(Blue);
  	GLCD_SetTextColor(White);
  	GLCD_DisplayString(0, 0, __FI, "    MCB1700 Demo    ");
  	GLCD_DisplayString(1, 0, __FI, "       Blinky       ");
  	GLCD_DisplayString(2, 0, __FI, "    www.keil.com    ");
  	GLCD_SetBackColor(White);
  	GLCD_SetTextColor(Blue);
  	GLCD_DisplayString(5, 0, __FI, "AD value:            ");
#endif

/* 9. Generate interrupt each 10 ms */																						
	SysTick_Config(SystemCoreClock/100);
	while (1)
	{         
		while(!ADC_DONE); // wait for ADC to finish
		ad_avg += ADC_GetCnv();
		ad_avg_count++;
		
		//every 16 values get new value
		if(ad_avg_count == 16)
		{
			ad_val_old = ad_val;
			ad_val = ad_avg / ad_avg_count;
			ad_avg_count = 0;
		}//if
		
		/* 	
			TODO
			Only change value if the average is different.
			Maybe just skip?
		*/
		
	sprintf(text, "0x%04X", ad_val);       // format text for print out     
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
    GLCD_DisplayString(5,  9, __FI,  (unsigned char *)text);
    GLCD_Bargraph (144, 6*24, 176, 20, (ad_val >> 2)); // max bargraph is 10 bit
#endif   
	}//while
}//main
