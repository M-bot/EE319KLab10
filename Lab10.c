#include "Matrix.h"
#include "Character.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#include "SysTickInts.h"
#include "ADC.h"

#define PI 3.141592654
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))



/*int main(void) {
  TExaS_Init();
  Graphics2DInit();
  while(1) {
		
		Render();
	}
}*/
int8_t Convert(uint32_t input){ //returns 1,0,or -1 depending on region of slide pot meter
  if(input>=(uint32_t)((0x0FFF)*(2/3)))
		return 1;
	else if (input<=((0x0FFF)*(1/3)))
		return -1;
	else
		return 0;
}
int isADCReady = 0;
int ADCData = 0;
int main(void){
  TExaS_Init();         // Bus clock is 80 MHz 
	Graphics2DInit();
  ST7735_InitR(INITR_REDTAB); 
	SysTick_Init(80000000/40);
  ADC_Init();         // turn on ADC, set channel to 1
  while(1){
		//while(!isADCReady);
		//isADCReady = 0;
		ADCData= ADC_In();
		int8_t Dir = Convert(ADCData);
		if(Dir!=0)
		{
			//PLACEHOLDERFUNCTION(Chacreter.sprite,CharacterMov(Dir)) //send x and y seperately
			 
		}
		
  }
}