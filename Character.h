//Create Character

#include "tm4c123gh6pm.h"
//input none
//output none
void Character_Init(void);


uint8_t Check_Collision(uint32_t test_x, uint32_t test_y, uint32_t test_width, uint32_t test_height);


//Update Issac Location
void Move(int8_t x,int8_t y);


void Place(int8_t x,int8_t y);

void Damage_Player(void);

uint8_t Get_Last_x(void);

uint8_t Get_Last_y(void);

uint8_t Get_x(void);

uint8_t Get_y(void);