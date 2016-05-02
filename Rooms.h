#include "tm4c123gh6pm.h"

typedef struct objects objects_t;
struct objects{
	uint8_t ID;     
	uint8_t xo;
	int8_t rangex;
	int8_t rangey;
	uint8_t Range;
	uint8_t Fire_Rate;
	uint8_t Fire_Tick;
	uint8_t Shot_Speed;
	uint8_t yo;
	uint8_t x;         //x coordinates
	uint8_t y;        //y coordinates
	uint8_t Last_x;   //Last x coordinate
	uint8_t Last_y;   //Last y coordinate
	uint8_t w;        //width
	uint8_t h;        //height
	int8_t veli;    // velocity in x direction
	int8_t velj;    // velocity in y direction
	uint8_t react;   //code for what happens if collided with, if 0=impassible and dont take damage, 1=impassible and take damage, 2=passable and take damage, 3=take damage then remove sprite
	uint8_t moves;  //boolean for move logic
	uint8_t fires;   //boolean for firing logic
	uint8_t Changes_Sprites; //boolean for animation
	uint8_t Current_Health; 
	uint8_t Move_Logic;   //0= chases character 1= moves randomly 2=moves away from character
	uint8_t speed;
	uint8_t Takes_Damage; //does it take damage?
	uint8_t Damage_To_Deal; //How much health to take off on a hit
	uint8_t Player; //is a players shot 0=false 1=true
	uint8_t Stat_to_change; //1=damage 2=fire_rate 3=Speed 4=Shot_Speed 5=Range 6=Max_Health 7=Current_Health
	uint8_t Stat_delta;
	uint8_t Arrow; //1=Left 2=UP 3=Down 4=right
	uint8_t Clearable; //0 if should be removed if room cleared, 1 if not
};

void Room_Init(uint8_t num,objects_t Objects[100]);