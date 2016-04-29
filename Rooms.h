#include "tm4c123gh6pm.h"

typedef struct objects objects_t;
struct objects{
	uint8_t ID;     
	uint8_t x;         //x coordinates
	uint8_t y;        //y coordinates
	uint8_t Last_x;   //Last x coordinate
	uint8_t Last_y;   //Last y coordinate
	uint8_t w;        //width
	uint8_t h;        //height
	uint8_t veli;    // velocity in x direction
	uint8_t velj;    // velocity in y direction
	uint8_t react;   //code for what happens if collided with, if 0=impassible and dont take damage, 1=impassible and take damage, 2=passable and take damage, 3=take damage then remove sprite
	uint8_t moves;  //boolean for move logic
	uint8_t fires;   //boolean for firing logic
	uint8_t Changes_Sprites; //boolean for animation
	uint8_t Current_Health; 
	uint8_t Move_Logic;   //0= chases character 1= moves randomly 2=moves away from character
	uint8_t speed;
};

void Room_Init(uint8_t num,objects_t Objects[30]);