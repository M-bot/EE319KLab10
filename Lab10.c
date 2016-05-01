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
#include "Timer1.h"
#include "Shot.h"
#include "Map.h"


#define PI 3.141592654
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))

int8_t mov[2];
int8_t fire[2];
int8_t mov_ready;
int8_t fire_ready;
uint8_t fire_checker=1;
uint8_t move_checker=1;
uint8_t size=100;
objects_t Objects[100];
void Timer0A_Run(void);
void Move_Towards(uint8_t i,uint8_t toX, uint8_t toY);
void Move_Random(uint8_t i);
void Move_Away(uint8_t i,uint8_t toX, uint8_t toY);
void Move_Directional(uint8_t i);

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
	uint8_t react;   //code for what happens if collided with, if 0=impassible and dont take damage, 1=impassible and take damage, 2=passable and take damage, 3=take damage then remove sprite 4=Impassible dont take damge and break tears
	uint8_t moves;  //boolean for move logic
	uint8_t fires;   //boolean for firing logic
	uint8_t Changes_Sprites; //boolean for animation
	uint8_t Current_Health; 
	uint8_t Move_Logic;  //0= chases character 1= moves randomly 2=moves away from character 3=Directional
	uint8_t Player //is a players shot 0=false 1=true
	uint8_t Takes_Damage; //does it take damage?
	uint8_t Damage_To_Deal; //How much health to take off on a hit
	
 
};*/
//typedef struct objects objects_t;



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
	SysTick_Init(80000000/20);
  ADC_Init();         // turn on ADC, set channel to 1
	Switch_Init(); //prepare Port B and D for switches
	Character_Init();
	Timer0_Init(Timer0A_Run,6000000);
	while(mov[0] == 0 && mov[1] == 0);
	Map_Init(ADC_In()+GPIO_PORTB_DATA_R); //This is so the random number generator actually generates a different map
	
	Room_Init(1,Objects);
  while(1){
		uint8_t newroom=1;        //check to see if a new room needs to be rendered, this logic will change!!!
		for(int i=0;i<size;i++)
			if(Objects[i].ID!=0)
				newroom=0;
		if(newroom)
			Room_Init(0,Objects);
		
		Render();
		
		
		if(invinc>0)    //i-frames
		 invinc--;

		if(mov_ready ==1)                                      //move player and any moving objects
		{
		Move(mov[0],mov[1],move_checker);
		mov_ready=0;
			for(int i =0;i<size;i++)
				{if(Objects[i].moves==1 && Objects[i].ID!=0)
					{
						if(Objects[i].Move_Logic==0)
							Move_Towards(i,Get_x(),Get_y());
						else if(Objects[i].Move_Logic==1)
							Move_Random(i);
						else if(Objects[i].Move_Logic==2)
							Move_Away(i,Get_x(),Get_y());
						else if(Objects[i].Move_Logic==3)
							Move_Directional(i);
					}
					
				}
		}
		uint8_t Collision;                                    //check for player collisions
			for(int i=0;i<size;i++)
			{
				if(Objects[i].ID!=0)
				{
					Collision=Check_Collision(Objects[i].x,Objects[i].y,Objects[i].w,Objects[i].h);    //Objects Collisions with Player!
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
								else if(Objects[i].react==3 && !(invinc) && Objects[i].Player==0)
								{
									Damage_Player();
									invinc=20;
									Objects[i].ID=RemoveSprite(Objects[i].ID);
								}
						}
				
						   //Objects Collisions with Objects
						
							for(int j=0;j<size;j++)
							{
								if(Objects[j].ID!=0)
								{
										uint8_t t1=0;
										uint8_t t2=0;
										for(int x1=0;x1<Objects[i].w;x1++)
												for(int x2 =0;x2<Objects[j].w;x2++)
															if((x1+Objects[i].x)==(x2+Objects[j].x))
															{
																t1=1;
																x1=Objects[i].w;
																x2=Objects[j].w;
															}
										for(int y1=0;y1<Objects[i].h;y1++)
											for(int y2 =0;y2<Objects[j].h;y2++)
												if((y1+Objects[i].y)==(y2+Objects[j].y))
												{
													t2=1;
													y1=Objects[i].h;
													y2=Objects[j].h;
				
												}
										if(t1 && t2)
										{
										if(Objects[i].Damage_To_Deal>0 && Objects[j].Takes_Damage==1 && Objects[i].Player==1 && i!=j) //if Objects J is damaged by tears
										{
											Objects[j].Current_Health-=Objects[i].Damage_To_Deal;
												if(Objects[j].Current_Health<=0)
													Objects[j].ID=RemoveSprite(Objects[j].ID);
											Objects[i].ID=RemoveSprite(Objects[i].ID);
									
										}
										else if(Objects[i].Damage_To_Deal>0 && Objects[j].react==4 && i!=j)  //If Object J breaks shots remove Object[i]
										{
											Objects[i].ID=RemoveSprite(Objects[i].ID);
										}
										else if(Objects[i].moves && Objects[j].react==0)
										{
											Objects[i].x=Objects[i].Last_x;
											Objects[i].y=Objects[i].Last_y;
											
											UpdateSprite(Objects[i].ID,Objects[i].x,Objects[i].y);
										}
										
									}
								
							}
						}
					
						
				}
				
			}
			if(fire_ready)    //create shots
			{
				fire_ready=0;
				uint8_t i=0;
				while(Objects[i].ID!=0)
					i++;
				if(fire[0] || fire[1])
				Create_Shot(fire[0],fire[1],&Objects[i]);
				
				for(int i=0;i<size;i++)
				{
					if(Objects[i].fires && Objects[i].ID!=0 )
					{
					  Objects[i].Fire_Tick++;
						if(Objects[i].Fire_Tick==Objects[i].Fire_Rate)
						{
							uint8_t j=0;
							while(Objects[j].ID!=0)
								j++;
							uint8_t cx=Get_x();
							uint8_t cy=Get_y();
							uint8_t cw=Get_Width();
							uint8_t ch=Get_Height();
						  Objects[j].x =  Objects[i].x;
							Objects[j].y = Objects[i].y;
							if(Objects[i].x>cx+cw & Objects[i].y>cy+ch)
							{
								Objects[j].x-=4;
								Objects[j].y+=Objects[i].h+2;
								Objects[j].veli=Objects[i].Shot_Speed*(-1);
								Objects[j].velj=Objects[i].Shot_Speed*(1);
							}
							else if(Objects[i].x>cx+cw & Objects[i].y>=cy & Objects[i].y<=cy+ch)
							{
								Objects[j].x-=4;
								Objects[j].y+=(Objects[i].h/2);
								Objects[j].veli=Objects[i].Shot_Speed*(-1);
								Objects[j].velj=0;
							}
							else if(Objects[i].x>cx+cw & Objects[i].y<cy)
							{
								Objects[j].x-=4;
								Objects[j].y-=4;
								Objects[j].veli=Objects[i].Shot_Speed*(-1);
								Objects[j].velj=Objects[i].Shot_Speed*(-1);
							}
							else if(Objects[i].x>=cx & Objects[i].x<=cx+cw & Objects[i].y>cy+ch)
							{
								Objects[j].x+=Objects[i].w/2;
								Objects[j].y-=4;
								Objects[j].veli=Objects[i].Shot_Speed*(0);
								Objects[j].velj=Objects[i].Shot_Speed*(-1);
							}
							else if(Objects[i].x>=cx & Objects[i].x<=cx+cw & Objects[i].y<cy)
							{ Objects[j].x+=Objects[i].w/2;
								Objects[j].y+=Objects[i].h+4;
								Objects[j].veli=Objects[i].Shot_Speed*(0);
								Objects[j].velj=Objects[i].Shot_Speed*(1);
							}
							else if(Objects[i].x<cx & Objects[i].y<cy)
							{
								Objects[j].x+=Objects[i].w;
								Objects[j].y+=Objects[i].h+4;
								Objects[j].veli=Objects[i].Shot_Speed*(1);
								Objects[j].velj=Objects[i].Shot_Speed*(1);
							}
							else if(Objects[i].x<cx & Objects[i].y>=cy & Objects[i].y<=cy+ch)
							{ Objects[j].x+=Objects[i].w;
								Objects[j].y+=Objects[i].h/2;
								Objects[j].veli=Objects[i].Shot_Speed*(1);
								Objects[j].velj=Objects[i].Shot_Speed*(0);
							}
							else if(Objects[i].x<cx & Objects[i].y>cy+ch)
							{	Objects[j].x+=Objects[i].w;
								Objects[j].y-=4;
								Objects[j].veli=Objects[i].Shot_Speed*(1);
								Objects[j].velj=Objects[i].Shot_Speed*(-1);
							}
							Objects[j].ID=Shot_Init(Objects[j].x,Objects[j].y);
							Objects[j].w=4;
							Objects[j].h=4;
							Objects[j].react=3;
							Objects[j].moves=1;
							Objects[j].fires=0;
							Objects[j].Changes_Sprites=0;
							Objects[j].Current_Health=1;
							Objects[j].Move_Logic=3;
							Objects[j].Player=0;
							Objects[j].xo=Objects[j].x;
							Objects[j].yo=Objects[j].y;
							Objects[j].rangex=Objects[i].Range;
							Objects[j].rangey=Objects[i].Range;
						
						Objects[i].Fire_Tick=0;
						} 
					}
				}
			}
		
		

			 
		
		
  }
}
void Timer0A_Run(void){
 if(fire_checker==0x10)
 {
		
		fire_checker=0;
	Fire_In(fire);
	fire_ready=1;
 }
 fire_checker++;
	Mov_In(mov);
	mov_ready=1;
	
}

void Move_Towards(uint8_t i,uint8_t toX, uint8_t toY)   //this does not include pathing...
{
	Objects[i].Last_x = Objects[i].x;
	Objects[i].Last_y = Objects[i].y;
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
	Objects[i].Last_x = Objects[i].x;
	Objects[i].Last_y = Objects[i].y;
	if(Objects[i].x<toX && Objects[i].x - Objects[i].speed>0)
		Objects[i].x -= Objects[i].speed;
	else if(Objects[i].x>toX && Objects[i].x + Objects[i].speed<140)
		Objects[i].x += Objects[i].speed;
	if(Objects[i].y<toY  && Objects[i].y - Objects[i].speed>0)
		Objects[i].y -= Objects[i].speed;
	else if(Objects[i].y>toY  && Objects[i].y +Objects[i].speed<140)
		Objects[i].y += Objects[i].speed;
	UpdateSprite(Objects[i].ID,Objects[i].x,Objects[i].y);
}
void Move_Directional(uint8_t i)
{
	if(Objects[i].veli<0)
	  Objects[i].rangex+= Objects[i].veli ;
	else
		Objects[i].rangex-= Objects[i].veli ;
	if(Objects[i].velj<0)
		Objects[i].rangey+= (Objects[i].velj);
	else
		Objects[i].rangey-= (Objects[i].velj);
	if(Objects[i].rangex<0 || Objects[i].rangey<0)
		Objects[i].ID=RemoveSprite(Objects[i].ID);
	Objects[i].Last_x = Objects[i].x;
	Objects[i].Last_y = Objects[i].y;
	if( (Objects[i].x+Objects[i].veli>140) || (Objects[i].x+Objects[i].veli<0))
	Objects[i].ID=RemoveSprite(Objects[i].ID);
	else if( (Objects[i].y+Objects[i].velj>80) || (Objects[i].y+Objects[i].velj<0))
		Objects[i].ID=RemoveSprite(Objects[i].ID);
	else
	{
	Objects[i].x+=Objects[i].veli;
	Objects[i].y+=Objects[i].velj;
	UpdateSprite(Objects[i].ID,Objects[i].x,Objects[i].y);
	}
	

}