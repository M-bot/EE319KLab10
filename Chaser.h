
#include "tm4c123gh6pm.h"

typedef struct objects objects_t;

uint8_t Chaser_Init(uint8_t x,uint8_t y);
	
void Chaser_Get_Loc(int8_t ID,int8_t array[4]);
void Chaser_Get_Logic(objects_t *o); 
uint8_t Pooter_Init(uint8_t x,uint8_t y);
void Pooter_Get_Logic(objects_t *o);
uint8_t Rock_Init(uint8_t x,uint8_t y);
void Rock_Get_Logic(objects_t *o);
uint8_t Pedestal_Init(uint8_t x,uint8_t y);
void Pedestal_Get_Logic(objects_t *o);