// UART.c
// Runs on LM4F120/TM4C123
// Provide functions that setup and interact with UART
// Last Modified: 4/12/2016 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "tm4c123gh6pm.h"

// UART initialization function 
// Input: none
// Output: none
void UART_Init(void){ 
	SYSCTL_RCGCUART_R |= 0x00000002;  	// activate UART1
  SYSCTL_RCGCGPIO_R |= 0x00000004;// activate port C
	UART1_CTL_R &= ~0x00000001;    	// disable UART
  UART1_IBRD_R = 50;     				 	// IBRD = int(80,000,000/(16*100,000)) = int(50.0)
  UART1_FBRD_R = 0;     					// FBRD = round(0.0 * 64) = 0
  UART1_LCRH_R = 0x00000070;  		// 8 bit, no parity bits, one stop, FIFOs
	
	UART1_IM_R |= 0x10;
	UART1_IFLS_R |= 0x10;
	UART1_IFLS_R &= ~0x28;
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFF0FFFFF)|0x00700000;
	NVIC_EN0_R |= 0x40;
	
  UART1_CTL_R |= 0x00000001;     	// enable UART
	
  GPIO_PORTC_AFSEL_R |= 0x30;    	// enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      	// configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;   	// disable analog on PC5-4
}

//------------UART_InChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
// *** Need not be busy-wait if you know when to call
char UART_InChar(void){  
  while((UART1_FR_R&0x0010) != 0);      // wait until RXFE is 0
  return((unsigned char)(UART1_DR_R&0xFF));
}

//------------UART_OutChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
void UART_OutChar(char data){  
  while((UART1_FR_R&0x0020) != 0);      // wait until TXFF is 0
  UART1_DR_R = data;
}
