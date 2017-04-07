#include "LPC17xx.H"                         /* LPC17xx definitions           */
//#include "ADC.h"

uint16_t AD_last;                            /* Last converted value          */
uint8_t  done = 0;                        /* AD conversion done flag       */

#define ADC_DONE (LPC_ADC->ADGDR >> 31)
#define ADC_LAST (LPC_ADC->ADGDR >> 4) & 0xFFF;
/*----------------------------------------------------------------------------
  Function that initializes ADC
 	
 *----------------------------------------------------------------------------*/
void ADC_Init (void) {
/* 1. enable power to ADC & IOCON   */																								
	 LPC_SC->PCONP |= (1 << 12);
	
/* 2. P0.25 is AD0.2 & no pull up/down   */
	LPC_PINCON->PINSEL1 |= (1 << 18);
	LPC_PINCON->PINMODE1 |= (0x2 << 18);
	
/* 3. select AD0.2 pin ,   ADC clock is 25MHz &  enable ADC          */
		LPC_ADC->ADCR= (0x10304);
	
/* ****  Part B:  Interrupt
	 13. 	i) A/D global interrupt enable       
        ii)enable ADC Interrupt using NVIC function         
*****/
	LPC_ADC->ADINTEN = (1 << 2);
	NVIC_EnableIRQ(ADC_IRQn);
	
}


/*----------------------------------------------------------------------------
  4. start AD Conversion
 *----------------------------------------------------------------------------*/
void ADC_StartCnv (void) {
  LPC_ADC->ADCR |= (1 << 24);
}


/*----------------------------------------------------------------------------
  5. stop AD Conversion
 *----------------------------------------------------------------------------*/
void ADC_StopCnv (void) {
	LPC_ADC->ADCR &= ~(1 << 24); //set conversion bit to 0
  
}


/*----------------------------------------------------------------------------
  6. Get converted AD value For Polling
 *----------------------------------------------------------------------------*/
uint16_t ADC_GetCnv (void) {

	while(!ADC_DONE); //wait until conversion flag
	AD_last = ADC_LAST; // store last value
	done = 1; //set done flag to 1
	return AD_last; //return last value
																						/* Wait for Conversion end       */
                                            /* Store converted value  */
																						// set AD conversion done flag to 1
                                            //Return Converted Value
}


/*----------------------------------------------------------------------------
  Part B- Interrupt
  
  14. A/D IRQ: Executed when A/D Conversion is done for Interrupt
 *----------------------------------------------------------------------------*/

void ADC_IRQHandler(void) {

	//while(!ADC_DONE);
	AD_last = ADC_LAST; //set value
	done = 1; //done
																					/* Store converted value   */
																					// set AD conversion done flag to 1
  
}
