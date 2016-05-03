#include <stdint.h>
#include "SoundController.h"
#include "UART.h"

// Requests to start playing the given sound as background music
void Sound_Init()
{
	int delay=0;
	SYSCTL_RCGCGPIO_R |= 0x20;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTF_DIR_R |=  0x0E;
	//GPIO_PORTD_DIR_R |= 0x80;
	GPIO_PORTF_DEN_R |= 0x0E;
	//GPIO_PORTD_DEN_R |= 0x80;
	GPIO_PORTF_AFSEL_R &= ~0x0E;
//	GPIO_PORTD_AFSEL_R &= 0x80;
	GPIO_PORTF_AMSEL_R &= ~0x0E;
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0;

}
void BGM_Start(uint8_t sound) {
	Sound_Transmit(sound,2);
}

// Requests to stop the background music
void BGM_Stop(void) {
	Sound_Transmit(0,2);
}

// Requests to play a sound
void Sound_Send(uint8_t sound) {
	GPIO_PORTF_DATA_R |= 0x08;
	GPIO_PORTF_DATA_R &= ~0x06;
	GPIO_PORTF_DATA_R |= (sound-1)<<1;
	
}

// Requests to play and then loop a sound
void Sound_Loop(uint8_t sound) {
	Sound_Transmit(sound,1);
}

// Requests to stop sound
void Sound_Stop(void) {
	GPIO_PORTF_DATA_R &= ~0x08;
}

// Internal use only
void Sound_Transmit(uint8_t sound, uint8_t loop) {
	UART_OutChar(0x02);
	UART_OutChar(sound);
	UART_OutChar(loop);
	UART_OutChar(0x00);
	UART_OutChar(0x00);
	UART_OutChar(0x00);
	UART_OutChar(0x00);
	UART_OutChar(0x03);
}
