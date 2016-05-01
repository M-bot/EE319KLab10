// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: Miguel Obregon
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
#define Dac_Bits 0x3F
#define Extra 0x10
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	volatile unsigned long delay;							
  SYSCTL_RCGC2_R |= 0x12;      											// 1) E
  delay = SYSCTL_RCGC2_R;      											// 2) wait
	GPIO_PORTE_AMSEL_R &= ~Dac_Bits; 									// 3) disable analog function on PE5-0
  GPIO_PORTE_PCTL_R &= ~0x00FFFFFF; 								// 4) enable regular GPIO
  GPIO_PORTE_DIR_R |= Dac_Bits;    									// 5) outputs on PE5-0
  GPIO_PORTE_AFSEL_R &= ~Dac_Bits; 									// 6) regular function on PE5-0
  GPIO_PORTE_DEN_R |= Dac_Bits;    									// 7) enable digital on PE5-0
	GPIO_PORTE_DR8R_R |= Dac_Bits;										// 8) prevent frying
	GPIO_PORTB_AMSEL_R &= ~Extra; 									// 3) disable analog function on PB4
  GPIO_PORTB_PCTL_R &= ~0x000F0000; 								// 4) enable regular GPIO
  GPIO_PORTB_DIR_R |= Extra;    									// 5) outputs on PB4
  GPIO_PORTB_AFSEL_R &= ~Extra; 									// 6) regular function on PB4
  GPIO_PORTB_DEN_R |= Extra;    									// 7) enable digital on PB4
	GPIO_PORTB_DR8R_R |= Extra;										// 8) prevent frying
}

// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(uint32_t data)
{
	GPIO_PORTE_DATA_R &= ~Dac_Bits;
	GPIO_PORTE_DATA_R |= Dac_Bits & data;
	GPIO_PORTB_DATA_R &= ~Extra;
	GPIO_PORTB_DATA_R |= (data >> 6) << 4;
}
