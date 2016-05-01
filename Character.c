#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#define PI 3.141592654
#include "Rooms.h"
#include "Shot.h"

#define LEFT -1;
#define STAY 0;
#define RIGHT 1;
//18x21
const unsigned short Character_Sprite[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x2946, 0x8416, 0x0000, 0x0000, 0x0000, 0x9CF8, 0x2946, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x420A, 0xB59D, 0x31A8, 0x2947, 0x422B, 0xC63F,
 0x420A, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x39A9, 0xC5FF, 0xC61F, 0xC5FF,
 0xC61F, 0xC61F, 0x39A9, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x420A, 0xCE5F,
 0xC63F, 0xC63F, 0xC63F, 0xCE5F, 0x420A, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
 0x10A3, 0x7BD4, 0x7394, 0x7393, 0x7393, 0x7BB3, 0x0000, 0x0000, 0x0862, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
 0xAD7C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xAD7C, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0x0000, 0x41EA, 0x8435, 0x9478, 0x94B8, 0x9CF9, 0xA4F9, 0xA4F9, 0x9CD9, 0x9499, 0x7394, 0x3188, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x5AAA, 0xB5BE, 0x9CF9, 0x8415, 0x8C37, 0x8C37, 0x8C37, 0x8C55, 0xAD5D, 0xAD5B, 0x4A67, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x4206, 0xDEB8, 0xC61F, 0x422C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6B52, 0xCE5F,
 0xEF17, 0x0861, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x4A6C, 0x9491, 0xE716, 0xE73A, 0x5AC8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x840E, 0xEF59, 0xF736, 0xB596, 0x4A6D, 0x0000, 0xFFFF, 0x0020, 0xBDBE, 0xAD76, 0xAD2F, 0xA510, 0x630B, 0x2967, 0x2126, 0x2126,
 0x2126, 0x2967, 0x738C, 0xAD30, 0xAD2F, 0xB5B9, 0xAD3B, 0x0000, 0xFFFF, 0x0020, 0xBDBE, 0x528D, 0x0000, 0x0000, 0x6B31, 0xC63F,
 0xBDFF, 0xC61F, 0xC5FF, 0xBDBF, 0x4A6C, 0x0000, 0x0000, 0x7392, 0xAD5C, 0x0000, 0xFFFF, 0x0020, 0xB5BE, 0xB5B9, 0x9492, 0x0000,
 0x6B51, 0xC61F, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDF, 0xBDDA, 0x94B2, 0x0020, 0x6B72, 0xAD7C, 0x0000, 0xFFFF, 0x0000, 0xB59E, 0xDEDF,
 0xCE7B, 0x3187, 0x7BD4, 0xBDBF, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDDE, 0xDEFF, 0xD6BB, 0x39C8, 0x8415, 0xAD7B, 0x0000, 0xFFFF, 0x0000,
 0xAD5C, 0xC61E, 0xC63F, 0xAD5D, 0xBDFE, 0xBDBE, 0xB5BD, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDFE, 0xBDDF, 0xAD5C, 0xB5BE, 0x8415, 0x0000,
 0xFFFF, 0x0000, 0x0000, 0x8C56, 0xC5FF, 0xBDDE, 0xBDDE, 0xBDBE, 0xBDBE, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xC5FE, 0x422B,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x94B9, 0xC5FF, 0xBDDE, 0xBDDE, 0xBDBE, 0xBDBE, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDDE,
 0x7BB3, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xB59D, 0xC5FF, 0xC63F, 0xC61F, 0xC63F, 0xC63F, 0xBDFF,
 0xC5FF, 0x8414, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x1082, 0x1083, 0x1083, 0x1083, 0x1082,
 0x1083, 0x1083, 0x1083, 0x10A3, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};

uint32_t Damage; 
uint32_t Fire_Rate;  //# Times per Second
uint32_t Speed;      //Pixels per second if held down
uint8_t Max_Health; //Multiples of two to correspond to half hearts
uint8_t Current_Health;  //""
uint32_t Shot_Speed;      // Tears pixels per second from when they are created
uint8_t Current_x;
uint8_t Current_y;
uint8_t Width;
uint8_t Height;
uint8_t ID;
uint8_t Last_x;
uint8_t Last_y;
uint8_t Range;
uint8_t Current_Fire_Rate;

void Character_Init(void)
{
		Range=25;
		Damage = 2;
		Fire_Rate = 5;
		Current_Fire_Rate=0;
		Speed = 3;
		Max_Health = 6;
		Current_Health =6;
	  Shot_Speed = 3;
		Width =18;
		Height =21;
	  Current_x = 61;
		Current_y = 30;
		ID = AddSprite(Character_Sprite,Width,Height,Current_x,Current_y);
	  DrawHearts(Current_Health,Max_Health);
	//	UpdateHeart(Max_Health,Current_Health);
	
}

uint8_t Check_Collision(uint8_t test_x, uint8_t test_y, uint8_t test_width, uint8_t test_height)
{
	uint8_t t1=0;
	uint8_t t2=0;
	for(int i=0;i<Width;i++)
		for(int x =0;x<test_width;x++)
			if((i+Current_x)==(x+test_x))
			{
				t1=1;
				i=Width;
				x=test_width;
			}
	for(int j=0;j<Height;j++)
		for(int y =0;y<test_height;y++)
			if((j+Current_y)==(y+test_y))
			{
				t2=1;
				j=Height;
				y=test_height;
				
			}
	return (t1 && t2);
}
	
void Move(int8_t x,int8_t y,uint8_t move_checker)
{
	
	if( (Current_x+Width + x*Speed)<=140 && (int8_t)(Current_x + x*Speed)>=0)
	{
		/*if(x!=0 && y!=0)
		{
			Current_x= Current_x*10 +(int8_t)((x*Speed*10)/(int8_t)sqrt(2));
			Current_x = Current_x/10 + (Current_x%10)/5;
		}
		else*/
		Last_x= Current_x;
		Current_x += x*Speed;
	}
	if( (Current_y+Height + y*Speed)<=80 && (int8_t)(Current_y + y*Speed)>=0)
	{
		/*if(x!=0 && y!=0)
		{
			Current_y= Current_y*10 +(int8_t)((y*Speed*10)/(int8_t)sqrt(2));
			Current_y= Current_y/10 + (Current_y%10)/5;
		}
		else*/
		Last_y=Current_y;
		Current_y += y*Speed;
		
	}
	//if(x!=0 && y!=0)
	UpdateSprite(ID,Current_x,Current_y);
	
}
void Place(int8_t x,int8_t y)
{
	UpdateSprite(ID,x,y);
	Last_x=Current_x;
	Last_y=Current_y;
	Current_x=x;
	Current_y=y;
}
void Damage_Player(void)
{
	Current_Health--;
	UpdateHeart(Max_Health,Current_Health);
	if(Current_Health==0)
	{
		RemoveSprite(ID);
		UpdateHeart(0,6);
	}
}
uint8_t Get_Last_x(void)
{
	return Last_x;
}
uint8_t Get_Last_y(void)
{
	return Last_y;
}
uint8_t Get_x(void)
{
	return Current_x;
}
uint8_t Get_y(void)
{
	return Current_y;
}
uint8_t Fire_Shot(void)
{
	if(Fire_Rate==Current_Fire_Rate)
	{
	Current_Fire_Rate=0;
	 return 1;
		
	}
	Current_Fire_Rate++;
	return 0;
	
}
void Create_Shot(int8_t xdir,int8_t ydir,objects_t *o)
{
	uint8_t x =  Current_x;
	uint8_t y = Current_y;
	if(xdir==-1 & ydir ==1)
	{
		x-=4;
		y+=Height+2;
	}
	else if(xdir==-1 & ydir ==0)
	{
		x-=4;
		y+=(Height/2);
	}
	else if(xdir==-1 & ydir ==-1)
	{
		x-=4;
		y-=4;
	}
	else if(xdir==0 & ydir ==-1)
	{
		x+=Width/2;
		y-=4;
	}
	else if(xdir==0 & ydir ==1)
	{ x+=Width/2;
		y+=Height+4;
	}
	else if(xdir==1 & ydir ==1)
	{
		x+=Width;
		y+=Height+4;
	}
	else if(xdir==1 & ydir ==0)
	{ x+=Width;
		y+=Height/2;
	}
	else if(xdir==1 & ydir ==-1)
	{	x+=Width;
		y-=4;
	}
	o->x=x;
	o->y=y;
  o->ID=Shot_Init(x,y);
	o->w=4;
	o->h=4;
	o->veli=Shot_Speed*(xdir);
	o->velj=Shot_Speed*(ydir);
	o->react=3;
	o->moves=1;
	o->fires=0;
	o->Changes_Sprites=0;
	o->Current_Health=1;
	o->Move_Logic=3;
	o->Damage_To_Deal=Damage;
	o->Player=1;
	o->xo=x;
	o->yo=y;
	o->rangex=Range;
	o->rangey=Range;
	
	
}
uint8_t Get_Width(void)
{
	return Width;
}
uint8_t Get_Height(void)
{
	return Height;
}