#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FiFo.h"
#include "TExaS.h"
#include "Sound.h"
#include "UART.h"
#include "ST7735.h"
#include "SoundController.h"
#include "Timer0.h"

#include "Sounds.h"

#define SIZE 4
const uint8_t * sounds[SIZE] = {seventy,Isaac_Hurt_Grunt0,Tears_Fire0,Door_Open};
uint32_t sizes[SIZE] = {60659,2241,631,1803};

const uint8_t silence[] = {0};

// Handles recieving frames
void UART1_Handler(void){
	while((UART1_FR_R&0x0010) == 0) {
		FiFo_Put(UART_InChar());
	}
	UART1_ICR_R = 0x10;
}

// For testing only, remove in final
void Transmit(void) {
	Sound_Send(2);
}

int main(void) {
	uint8_t sound;
	uint8_t loop;
	TExaS_Init();
	ST7735_InitR(INITR_REDTAB);
	UART_Init();
	FiFo_Init();
	Sound_Init();
	Timer0_Init(Transmit,80000000*2);
	// For testing only
	BGM_Start(0);
	while(1) {
		char data;
		while(!FiFo_Get(&data));
		ST7735_SetCursor(0,0);	
		while(!FiFo_Get(&data));
		sound = data;
		while(!FiFo_Get(&data));
		loop = data;
		if(sound == 0) {
			if(loop == 2)
				Sound_BGM_Play(silence,1);
			Sound_Play(silence,1,1);
		}
		if(sound > 0 && sound <= SIZE) {
			if(loop == 2) {
				Sound_BGM_Play(sounds[sound-1],sizes[sound-1]);
			}
			else {
				Sound_Play(sounds[sound-1],sizes[sound-1],loop);
			}
		}
		for(int x = 0; x < 5; x++) {
			while(!FiFo_Get(&data));
		}
	}
}
