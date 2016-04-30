#include <stdint.h>
#include "SoundController.h"
#include "UART.h"

// Requests to start playing the given sound as background music
void BGM_Start(uint8_t sound) {
	Sound_Transmit(sound,2);
}

// Requests to stop the background music
void BGM_Stop(void) {
	Sound_Transmit(0,2);
}

// Requests to play a sound
void Sound_Send(uint8_t sound) {
	Sound_Transmit(sound,0);
}

// Requests to play and then loop a sound
void Sound_Loop(uint8_t sound) {
	Sound_Transmit(sound,1);
}

// Requests to stop sound
void Sound_Stop(void) {
	Sound_Transmit(0,0);
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
