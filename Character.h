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

uint8_t Fire_Shot(void);

void Create_Shot(int8_t xdir,int8_t ydir,objects_t *o);
void Update_Stats(uint8_t code, uint8_t delta);
void Update_Damage(int8_t delta);

void Update_Fire_Rate(int8_t delta);

void Update_Speed(int8_t delta);

void Update_Shot_Speed(int8_t delta);

void Update_Range(int8_t delta);

void Update_Max_Health(int8_t delta);
void Update_Current_Health(int8_t delta);

void Sprite_Still(void);
void Sprite_Move_2(void);

void Sprite_Move_1(void);
