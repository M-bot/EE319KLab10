
typedef struct objects objects_t;
#include "tm4c123gh6pm.h"
uint8_t Heart_Item_Init(uint8_t x,uint8_t y);


void Heart_Item_Update();
void Heart_Item_Get_Logic(objects_t *o) ;

uint8_t Blood_Bag_Item_Init();

void Blood_Bag_Item_Update();

void Blood_Bag_Item_Get_Logic(objects_t *o) ;
uint8_t Blood_Clot_Item_Init();

void Blood_Clot_Item_Update();


void Blood_Clot_Item_Get_Logic(objects_t *o) ;

uint8_t Blue_Cap_Item_Init();
void Blue_Cap_Item_Update();
void Blue_Cap_Item_Get_Logic(objects_t *o) ;