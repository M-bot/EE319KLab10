#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#include "Rooms.h"
#define PI 3.141592654

#define LEFT -1;
#define STAY 0;
#define RIGHT 1;
//14x10

const unsigned short Pooter[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x4A6A, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0x0842, 0xA514, 0xB596, 0x738E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x632D,
 0x94B2, 0xC638, 0xCE59, 0x2125, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x18E4, 0x9CF3, 0x6B6D, 0x18E4,
 0x2946, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0841, 0x0000, 0x0021, 0x0000, 0x0000,
 0x2125, 0x0000, 0x0001, 0xFFFF, 0x0862, 0xC618, 0xC618, 0xC618, 0xC618, 0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0x0842,
 0xC618, 0x0862, 0x0000, 0xC618, 0xC618, 0xC618, 0xC618, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2945, 0xC618, 0xC618, 0x0000,
 0xFFFF, 0x0000, 0xC618, 0xC618, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xC618, 0xC618, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF,

};





//uint32_t Fire_Rate=0;  //# Times per Second
//uint32_t Speed=1;      //Pixels per second if held down
//uint8_t Max_Health=10; //Multiples of two to correspond to half hearts


uint8_t Pooter_Init(uint8_t x,uint8_t y)
{
	uint8_t id = AddSprite(Pooter,14,10,x,y);
//	Render();
	return(id);
	
}

/*uint8_t Check_Collision(uint8_t test_x, uint8_t test_y, uint8_t test_width, uint8_t test_height)
{
	for(int i=0;i<arr[i].Width;i++)
		for(int x =0;x<test_width;x++)
			if((i+arr[i].Width)==(x+test_width))
				return 1;
	for(int j=0;j<arr[i].Height;j++)
		for(int y =0;y<test_height;y++)
			if((y+arr[i].Height)==(y+test_height))
				return 1;
	return 0;
}*/
	
/*void Move(int8_t x,int8_t y)
{
	if( (Current_x+Width + x*(Speed))<=140 && (int8_t)(Current_x + x*(Speed))>=0)
	{
		if(x!=0 && y!=0)
		{
			Current_x= Current_x*10 +(int8_t)((x*Speed*10)/(int8_t)sqrt(2));
			Current_x = Current_x/10 + (Current_x%10)/5;
		}
		else*/
	//	Current_x += x*(Speed);
/*
	if( (Current_y+Height + y*(Speed))<=80 && (int8_t)(Current_y + y*(Speed))>=0)
	{
		if(x!=0 && y!=0)
		{
			Current_y= Current_y*10 +(int8_t)((y*Speed*10)/(int8_t)sqrt(2));
			Current_y= Current_y/10 + (Current_y%10)/5;
		}
		else*/
	//	Current_y += y*(Speed);
	//}
	//if(x!=0 && y!=0)
	//UpdateSprite(ID,Current_x,Current_y);
///}
void Pooter_Get_Loc(int8_t ID,int8_t array[4])
{

}	
void Pooter_Get_Logic(objects_t *o) // array[0]=width array[1]=height  array[2]=veli  array[3]=velj  array[4]=reacts    array[5]=moves array[6]=fires array[7]=Changes_Sprites
{
	o->w=14;
	o->h=10;
	o->veli=0;
	o->velj=0;
	o->react=2;
	o->moves=0;
	o->fires=1;
	o->Changes_Sprites=0;
	o->Current_Health=10;
	o->Move_Logic=0;
	o->speed=1;
	o->Takes_Damage=1;
	
}

