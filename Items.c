#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#include "Rooms.h"
#include "Character.h"
#define PI 3.141592654

const unsigned short heart[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x18CF, 0x0001,
 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x2134, 0x2134, 0x2134, 0x2134, 0x2134, 0x18CF, 0x0001, 0xFFFF, 0x0001, 0x18CF,
 0x2134, 0x18CF, 0x2134, 0x423B, 0x423B, 0x2134, 0x0001, 0xFFFF, 0x0001, 0x2134, 0x423B, 0x2134, 0x2134, 0x2134, 0x423B, 0x2134,
 0x0001, 0xFFFF, 0x0001, 0x2134, 0x2134, 0x18CF, 0x18CF, 0x18CF, 0x2134, 0x18CF, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x18CF,
 0x2134, 0x2134, 0x2134, 0x18CF, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x2134, 0x2134, 0x0001, 0x2134, 0x2134, 0x0001,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x2134, 0x2134, 0x0001, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};

const unsigned short bloodbag[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x0001, 0xFFFF, 0x0001, 0xFFFF,
 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x0001, 0xFFFF, 0x0001, 0x0001, 0x4A49, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0x0001, 0x000B, 0x0010, 0x0010, 0x0010, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0010, 0x0010, 0x0010, 0x0010, 0x0008,
 0x0010, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0xC618,
 0x0019, 0x0010, 0x0010, 0x0010, 0x0010, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0xC618, 0xC618, 0x0019, 0x0019, 0x0019, 0x0019, 0x0001,
 0xFFFF, 0xFFFF, 0x0001, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0xC618, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0xC618, 0xC618, 0xC618,
 0xC618, 0xC618, 0xC618, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0xAD55, 0xC618, 0xC618, 0xC618, 0xC618, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF, 0xFFFF,

};

const unsigned short bloodclot[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x0001, 0x0013, 0x0001,
 0x0001, 0x0001, 0x0001, 0xFFFF, 0x0001, 0x000D, 0x0019, 0x0013, 0x0013, 0x0013, 0x0013, 0x0013, 0x000D, 0x0001, 0xFFFF, 0x0001,
 0x0001, 0x0013, 0x0013, 0x0013, 0x0013, 0x000D, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0x0013, 0x0019, 0x0019, 0x0019, 0x0019, 0x0013,
 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0xEF5D, 0x0019, 0x0019, 0x0019, 0x0019, 0x0019, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0xEF5D, 0x0019,
 0x0019, 0x0019, 0x0019, 0x0019, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0x0019, 0xEF5D, 0xEF5D, 0x0019, 0x0019, 0x0013, 0x0001, 0xFFFF,
 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x0019, 0x0019, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};


const unsigned short bluecap[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0xCCD3, 0xCCD3,
 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0xE618, 0xE618, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0001, 0x0001, 0xE618, 0xE618, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0xE618, 0x0001, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x7A04,
 0x9285, 0x9285, 0x7A04, 0x0001, 0x0001, 0xFFFF, 0x0001, 0x7A04, 0x9285, 0x9285, 0x9285, 0x9285, 0x9285, 0x9285, 0x7A04, 0x0001,
 0x0001, 0x9285, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0x9285, 0x0001, 0x0001, 0x9285, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6,
 0xB2E6, 0xB2E6, 0x9285, 0x0001, 0xFFFF, 0x0001, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0x0001, 0xFFFF, 0xFFFF, 0x0001,
 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0x9285, 0xB2E6, 0xB2E6, 0xB2E6, 0xB2E6, 0x9285,
 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x9285, 0x9285, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};



uint8_t Heart_Item_Init(uint8_t x,uint8_t y)
{
	return (AddSprite(heart,10,10,x,y));
} 

void Heart_Item_Update()
{
	Update_Stats(6,1);
	Update_Stats(7,3);
}

void Heart_Item_Get_Logic(objects_t *o) 
{
	o->Last_x=o->x;
	o->Last_y=o->y;
	o->w=10;
	o->h=10;
	o->veli=0;
	o->velj=0;
	o->react=1; // ???????
	o->moves=0;
	o->fires=0;
	o->Changes_Sprites=0;
	o->Clearable=1;
	o->Item=1;
	o->Update = Heart_Item_Update; 
}

uint8_t Blood_Bag_Item_Init()
{
	return (AddSprite(bloodbag,10,10,140/2-5,70/2-5));
} 

void Blood_Bag_Item_Update()
{
	Update_Stats(6,1);
	Update_Stats(7,5);
}

void Blood_Bag_Item_Get_Logic(objects_t *o) 
{
	o->Last_x=o->x;
	o->Last_y=o->y;
	o->w=10;
	o->h=10;
	o->veli=0;
	o->velj=0;
	o->react=1; // ???????
	o->moves=0;
	o->fires=0;
	o->Changes_Sprites=0;
	o->Clearable=1;
	o->Item=1;
	o->Update = Blood_Bag_Item_Update; 
}

uint8_t Blood_Clot_Item_Init()
{
	return (AddSprite(bloodclot,10,10,140/2-5,70/2-5));
} 

void Blood_Clot_Item_Update()
{
	Update_Stats(1,1);
	Update_Stats(5,5);
}

void Blood_Clot_Item_Get_Logic(objects_t *o) 
{
	o->Last_x=o->x;
	o->Last_y=o->y;
	o->w=10;
	o->h=10;
	o->veli=0;
	o->velj=0;
	o->react=1; // ???????
	o->moves=0;
	o->fires=0;
	o->Changes_Sprites=0;
	o->Clearable=1;
	o->Item=1;
	o->Update = Blood_Clot_Item_Update; 
}

uint8_t Blue_Cap_Item_Init()
{
	return (AddSprite(bluecap,10,10,140/2-5,70/2-5));
} 

void Blue_Cap_Item_Update()
{
	Update_Stats(6,1);
	Update_Stats(2,1);
	Update_Stats(3,-1);
}

void Blue_Cap_Item_Get_Logic(objects_t *o) 
{
	o->Last_x=o->x;
	o->Last_y=o->y;
	o->w=10;
	o->h=10;
	o->veli=0;
	o->velj=0;
	o->react=1; // ???????
	o->moves=0;
	o->fires=0;
	o->Changes_Sprites=0;
	o->Clearable=1;
	o->Item=1;
	o->Update = Blue_Cap_Item_Update; 
}