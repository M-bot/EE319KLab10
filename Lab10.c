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
#include "5Pos_Switch.h"
#include "Timer0.h"
#include "Chaser.h"

#define PI 3.141592654
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))

int8_t mov[2];
int8_t fire[2];
int8_t mov_ready;
void Timer0A_Run(void);
/*int main(void) {
  TExaS_Init();
  Graphics2DInit();
  while(1) {
		
		Render();
	}
}*/
/*int8_t Convert(uint32_t input){ //returns 1,0,or -1 depending on region of slide pot meter
  if(input>=(uint32_t)((0x0FFF)*(2/3)))
		return 1;
	else if (input<=((0x0FFF)*(1/3)))
		return -1;
	else
		return 0;
}*/
uint8_t Chasers[8];
uint8_t *ChasersPt =Chasers;
int isSensorReady = 0;
int ADCData = 0;
int main(void){
  TExaS_Init();         // Bus clock is 80 MHz 
	Graphics2DInit();
  //ST7735_InitR(INITR_REDTAB); 
	SysTick_Init(80000000/20);
  ADC_Init();         // turn on ADC, set channel to 1
	Switch_Init(); //prepare Port B and D for switches
	Character_Init();
	Timer0_Init(Timer0A_Run,4000000); 
	*ChasersPt=Chaser_Init();
	ChasersPt++;
  while(1){
		Render();
		//while(!isADCReady);
		//uint32_t i =0x008FFFFF; 
		//while(!isSensorReady)
		//isSensorReady=0;
		if(mov_ready ==1)
		{
		Move(mov[0],mov[1]);
		mov_ready=0;
		}
		int8_t coords[4];
		uint8_t damage;
		for(int i=0;i<8;i++)
			if(Chasers[i]!=0)
			{
 				Chaser_Get_Loc(Chasers[i],coords);
				damage=Check_Collision(coords[0],coords[1],coords[2],coords[3]);
				if(damage)
					Place(90,50);
			}
		

			//PLACEHOLDERFUNCTION(Chacreter.sprite,CharacterMov(Dir)) //send x and y seperately
			 
		
		
  }
}
void Timer0A_Run(void){
	Mov_In(mov);
	mov_ready=1;
	
}
void SysTick_Handler(void){
  //PF2 ^= 0x04;      // Heartbeat
  //PF2 ^= 0x04;      // Heartbeat
	//ADCData = ADC_In();
	isSensorReady = 1;
  //PF2 ^= 0x04;      // Heartbeat
}