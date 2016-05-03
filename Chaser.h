
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
uint8_t Arrow_Right_Init();
uint8_t Arrow_Up_Init();
uint8_t Arrow_Left_Init();
uint8_t Arrow_Down_Init();

uint8_t Horf_Init(uint8_t x,uint8_t y);
uint8_t Fatty_Init(uint8_t x,uint8_t y);

uint8_t Attack_Fly_Init(uint8_t x,uint8_t y);

void Fatty_Get_Logic(objects_t *o) ;

void Attack_Fly_Logic(objects_t *o) ;

void Horf_Get_Logic(objects_t *o) ;