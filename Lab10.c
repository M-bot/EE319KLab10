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
#include "Rooms.h"

#define PI 3.141592654
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))

int8_t mov[2];
int8_t fire[2];
int8_t mov_ready;
void Timer0A_Run(void);
void Move_Towards(uint8_t i,uint8_t toX, uint8_t toY);
void Move_Random(uint8_t i);
void Move_Away(uint8_t i,uint8_t toX, uint8_t toY);
/*struct objects{
	uint8_t ID;     
	uint8_t x;         //x coordinates
	uint8_t y;        //y coordinates
	uint8_t Last_x;   //Last x coordinate
	uint8_t Last_y;   //Last y coordinate
	uint8_t w;        //width
	uint8_t h;        //height
	uint8_t veli;    // velocity in x direction
	uint8_t velj;    // velocity in y direction
	uint8_t react;   //code for what happens if collided with, if 0=impassible and dont take damage, 1=impassible and take damage, 2=passable and take damage, 3=take damage then remove sprite
	uint8_t moves;  //boolean for move logic
	uint8_t fires;   //boolean for firing logic
	uint8_t Changes_Sprites; //boolean for animation
	uint8_t Current_Health; 
};*/
//typedef struct objects objects_t;

objects_t Objects[30];


/*int8_t Convert(uint32_t input){ //returns 1,0,or -1 depending on region of slide pot meter
  if(input>=(uint32_t)((0x0FFF)*(2/3)))
		return 1;
	else if (input<=((0x0FFF)*(1/3)))
		return -1;
	else
		return 0;
}*/
uint32_t invinc =0;
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
	
	Room_Init(0,Objects);
  while(1){
		uint8_t newroom=1;        //check to see if a new room needs to be rendered, this logic will change!!!
		for(int i=0;i<30;i++)
			if(Objects[i].ID!=0)
				newroom=0;
		if(newroom)
			Room_Init(0,Objects);
		
		Render();
		
		
		if(invinc>0)    //i-frames
		 invinc--;

		if(mov_ready ==1)                                      //move player and any moving objects
		{
		Move(mov[0],mov[1]);
		mov_ready=0;
			for(int i =0;i<30;i++)
				{if(Objects[i].moves==1)
					{
						if(Objects[i].Move_Logic==0)
							Move_Towards(i,Get_x(),Get_y());
						else if(Objects[i].Move_Logic==1)
							Move_Random(i);
						else
							Move_Away(i,Get_x(),Get_y());
					}
					
				}
		}
		uint8_t Collision;                                    //check for player collisions
			for(int i=0;i<30;i++)
			{
				if(Objects[i].ID!=0)
				{
					Collision=Check_Collision(Objects[i].x,Objects[i].y,Objects[i].w,Objects[i].h);   
						if(Collision)
						{
								if(Objects[i].react==2 && !(invinc))
								{
								Damage_Player();
								invinc=20;
								}
								else if(Objects[i].react==0)
								{
									Place(Get_Last_x(),Get_Last_y());
								}
						}
						
				}
			}
		
		

			 
		
		
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
void Move_Towards(uint8_t i,uint8_t toX, uint8_t toY)   //this does not include pathing...
{
	if(Objects[i].x<toX)
		Objects[i].x += Objects[i].speed;
	else if(Objects[i].x>toX)
		Objects[i].x -= Objects[i].speed;
	if(Objects[i].y<toY)
		Objects[i].y += Objects[i].speed;
	else if(Objects[i].y>toY)
		Objects[i].y -= Objects[i].speed;
	UpdateSprite(Objects[i].ID,Objects[i].x,Objects[i].y);
}
void Move_Random(uint8_t i)
{

}

void Move_Away(uint8_t i,uint8_t toX, uint8_t toY)
{
	
}