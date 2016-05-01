//Create Character

#include "tm4c123gh6pm.h"
//input none
//output none
void Character_Init(void);
uint8_t Get_Width(void);
uint8_t Get_Height(void);
typedef struct objects objects_t;


uint8_t Check_Collision(uint32_t test_x, uint32_t test_y, uint32_t test_width, uint32_t test_height);


//Update Issac Location
void Move(int8_t x,int8_t y,uint8_t move_checker);


void Place(int8_t x,int8_t y);

void Damage_Player(void);

uint8_t Get_Last_x(void);

uint8_t Get_Last_y(void);

uint8_t Get_x(void);

uint8_t Get_y(void);

uint8_t Fire_Shot(uint8_t check);

void Create_Shot(int8_t xdir,int8_t ydir,objects_t *o);