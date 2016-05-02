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
void Update_Objects(uint8_t i);
uint8_t Get_Next_Object(void);
uint8_t Check_Room_Visited(uint8_t i);
void Set_Room_Visited(void);
uint8_t Set_Map_Index(uint8_t x,uint8_t y);
void Remove_Visited_Sprites(void);
uint8_t map_index;
void Remove_All_Sprites(void);

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
	uint8_t Arrow; //1=Left 2=UP 3=Down 4=right
 
};*/
struct map_of_objects{
	uint8_t visited;
	uint8_t room_x;
	uint8_t room_y;
};
typedef struct map_of_objects mapo_t;
mapo_t map_of_objects[25];

uint32_t invinc =0;
int isSensorReady = 0;
int ADCData = 0;
int main(void){
  TExaS_Init();         // Bus clock is 80 MHz 
	Graphics2DInit();
	ADC_Init();         // turn on ADC, set channel to 1
	Switch_Init(); //prepare Port B and D for switches
	Character_Init();
	Timer0_Init(Timer0A_Run,6000000);
	//while(mov[0] == 0 && mov[1] == 0);
	Map_Init(ADC_In()+GPIO_PORTB_DATA_R); //This is so the random number generator actually generates a different map
	uint8_t Center = Get_Center();
	uint8_t Current_Room[2]={Center,Center};
	uint8_t Next_Object_Index;
	Room_Init(Get_Room_Data(Current_Room[0],Current_Room[1]),Objects);
	uint8_t map_index=0;
	map_of_objects[map_index].room_x=Current_Room[0];
	map_of_objects[map_index].room_y=Current_Room[1];
	for(uint8_t i=0;i<25;i++)
		map_of_objects[i].visited=0;
  while(1)
	{
		
		uint8_t moverooms=1;        //check to see if a new room needs to be rendered, this logic will change!!!
		for(int i=0;i<size;i++)
			if(Objects[i].Takes_Damage==1 && Objects[i].ID!=0)
				moverooms=0;
		for(int i=0;i<size;i++)
				if(Objects[i].Arrow!=0 && Objects[i].ID!=0)
					moverooms=0;
		uint8_t achieved=0;
		if(moverooms && fire_checker>20 && !achieved)
		{
			achieved=1;
			map_of_objects[map_index].visited=1;
			if(Get_Room_Data(Current_Room[0]+1,Current_Room[1])!=0)
			{
				Next_Object_Index=Get_Next_Object();
				Objects[Next_Object_Index].ID =Arrow_Left_Init();
				Objects[Next_Object_Index].Arrow=1;
				Objects[Next_Object_Index].x=1;
				Objects[Next_Object_Index].y=38;
				Objects[Next_Object_Index].w=7;
				Objects[Next_Object_Index].h=5;
				
			}
			if(Get_Room_Data(Current_Room[0],Current_Room[1]+1)!=0)
			{
				Next_Object_Index=Get_Next_Object();
				Objects[Next_Object_Index].ID =Arrow_Up_Init();
				Objects[Next_Object_Index].Arrow=2;
				Objects[Next_Object_Index].x=68;
				Objects[Next_Object_Index].y=1;
				Objects[Next_Object_Index].w=5;
				Objects[Next_Object_Index].h=7;
			}
			if(Get_Room_Data(Current_Room[0]-1,Current_Room[1])!=0)
			{
				Next_Object_Index=Get_Next_Object();
				Objects[Next_Object_Index].ID =Arrow_Right_Init();
				Objects[Next_Object_Index].Arrow=4;
				Objects[Next_Object_Index].x=137;
				Objects[Next_Object_Index].y=38;
				Objects[Next_Object_Index].w=7;
				Objects[Next_Object_Index].h=5;
			}
			if(Get_Room_Data(Current_Room[0],Current_Room[1]-1)!=0)
			{
				Next_Object_Index=Get_Next_Object();
				Objects[Next_Object_Index].ID =Arrow_Down_Init();
				Objects[Next_Object_Index].Arrow=3;
				Objects[Next_Object_Index].x=68;
				Objects[Next_Object_Index].y=73;
				Objects[Next_Object_Index].w=5;
				Objects[Next_Object_Index].h=7;
			}
			
		}
		
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
								else if(Objects[i].Arrow!=0)
								{
									
									Remove_All_Sprites();
									Set_Room(Current_Room[0],Current_Room[1],1);
									Set_Room(Current_Room[0],Current_Room[1],2);
									switch(Objects[i].Arrow)
									{
										//Set_Room_Visited();
										case 1:
											Place(140-Get_Width(),40-(Get_Height()/2));
											Current_Room[0]+=1;
											break;
										case 2:
											Place(70-(Get_Width()/2),80-(Get_Height()));
											Current_Room[1]+=1;
											break;
										case 3:
											Place(70-(Get_Width()/2),1);
											Current_Room[1]-=1;
											break;
										case 4:
											Place(1,40-(Get_Height()/2));
											Current_Room[0]-=1;
											break;			
									}
									Room_Init(Get_Room_Data(Current_Room[0],Current_Room[1]),Objects);
									Set_Room(Current_Room[0],Current_Room[1],0);
									map_index=Set_Map_Index(Current_Room[0],Current_Room[1]);
									//map_of_objects[map_index].visited=0;
									if(Check_Room_Visited(map_index))
										Remove_Visited_Sprites();
									fire_checker=0;
									
										
										
									
								}
								else if(Objects[i].react==0 || Objects[i].react==4)
								{
									Place(Get_Last_x(),Get_Last_y());
								}
								else if(Objects[i].react==3 && !(invinc) && Objects[i].Player==0)
								{
									Damage_Player();
									invinc=20;
									Objects[i].ID=RemoveSprite(Objects[i].ID);
								}
								else if(Objects[i].Stat_to_change!=0)                                    //code for detecting items to be picked up
								{
									Update_Stats(Objects[i].Stat_to_change,Objects[i].Stat_delta);
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
										else if(Objects[i].moves && (Objects[j].react==0  || Objects[j].react==4))
										{
											Objects[i].x=Objects[i].Last_x;
											Objects[i].y=Objects[i].Last_y;
											
											UpdateSprite(Objects[i].ID,Objects[i].x,Objects[i].y);
										}
										if((Objects[i].veli!=0 || Objects[i].velj!=0) && Objects[j].react==4)
										{
											Objects[i].ID=RemoveSprite(Objects[i].ID);
										}
									}
								
							}
						}
					
						
				}
				
			}
			if(fire_ready)    //create shots
			{
				fire_ready=0;
				uint8_t i=Get_Next_Object();
				
				if((fire[0] || fire[1]) && (Fire_Shot()))
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
							Objects[j].ID=Shot_E_Init(Objects[j].x,Objects[j].y);
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
 
	Fire_In(fire);
	fire_ready=1;
 
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
uint8_t Get_Next_Object(void)
{
	uint8_t i=0;
	while(Objects[i].ID!=0)
		i++;
	     
	Objects[i].xo=0;
	Objects[i].rangex=0;
	Objects[i].rangey=0;
	Objects[i].Range=0;
	Objects[i].Fire_Rate=0;
	Objects[i].Fire_Tick=0;
	Objects[i].Shot_Speed=0;
	Objects[i].yo=0;
	Objects[i].x=0;       
	Objects[i].y=0;       
	Objects[i].Last_x=0;  
	Objects[i].Last_y=0;   
	Objects[i].w=0;     
	Objects[i].h=0;     
	Objects[i].veli=0;   
	Objects[i].velj=0;   
	Objects[i].react=10;  
	Objects[i].moves=0; 
	Objects[i].fires=0;
	Objects[i].Changes_Sprites=0; 
	Objects[i].Current_Health=0; 
	Objects[i].Move_Logic=0;  
	Objects[i].speed=0;
	Objects[i].Takes_Damage=0; 
	Objects[i].Damage_To_Deal=0; 
	Objects[i].Player=0; 
	Objects[i].Stat_to_change=0; 
	Objects[i].Stat_delta=0;
	Objects[i].Arrow=0; 
	Objects[i].Clearable=0;
		
	return i;
}
void Set_Room_Visited(void)
{
	map_of_objects[map_index].visited=1;
}
uint8_t Check_Room_Visited(uint8_t i)
{
	if(map_of_objects[i].visited==1)
	{
			return 1;
	}
	return 0;
}
void Remove_Visited_Sprites(void)
{
	for(int i=0;i<size;i++)
		if(Objects[i].Clearable==1)
			Objects[i].ID=RemoveSprite(Objects[i].ID);
		
}
uint8_t Set_Map_Index(uint8_t x,uint8_t y)
{
	for(uint8_t i=0;i<25;i++)
		if(map_of_objects[i].room_x==x && map_of_objects[i].room_y==y)
			return i;
	for(uint8_t i =0;i<25;i++)
		{
			if(map_of_objects[i].visited==0)
			{
				map_of_objects[i].room_x=x;
				map_of_objects[i].room_y=y;
				return i;
			}
		}
}
void Remove_All_Sprites(void)
{
	for(int i=0;i<size;i++)
	{
		if(Objects[i].ID!=0)
			Objects[i].ID=RemoveSprite(Objects[i].ID);
		
	}
	
}
