
#include "tm4c123gh6pm.h"

typedef struct objects objects_t;

uint8_t Chaser_Init(uint8_t x,uint8_t y);
	
void Chaser_Get_Loc(int8_t ID,int8_t array[4]);
void Chaser_Get_Logic(objects_t *o); // array[0]=width array[1]=height  array[2]=veli  array[3]=velj  array[4]=reacts    array[5]=moves array[6]=fires array[7]=Changes_Sprites