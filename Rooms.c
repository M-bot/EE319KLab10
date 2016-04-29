#include "Matrix.h"
#include "Character.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#include "SysTickInts.h"
#include "ADC.h"
#include "5Pos_Switch.h"
#include "Timer0.h"
#include "Chaser.h"
#include "Pooter.h"

struct objects{
	uint8_t ID;     
	uint8_t x;         //x coordinates
	uint8_t y;        //y coordinates
	uint8_t Last_x;   //Last x coordinate
	uint8_t Last_y;   //Last y coordinate
	uint8_t w;        //width
	uint8_t h;        //height
	int8_t veli;    // velocity in x direction
	int8_t velj;    // velocity in y direction
	uint8_t react;   //code for what happens if collided with, if 0=impassible and dont take damage, 1=impassible and take damage, 2=passable and take damage, 3=take damage then remove sprite
	uint8_t Takes_Damage; //does it take damage?
	uint8_t Damage_To_Deal; //How much health to take off on a hit
	uint8_t moves;  //boolean for move logic
	uint8_t fires;   //boolean for firing logic
	uint8_t Changes_Sprites; //boolean for animation
	uint8_t Current_Health; //current health of object
	uint8_t Move_Logic;  //0= chases character 1= moves randomly 2=moves away from character 3=Directional
	uint8_t speed;   //how fast it moves
	uint8_t Player; //is a players shot 0=false 1=true
};
typedef struct objects objects_t;

void Room_Init(uint8_t num,objects_t Objects[30])
{uint8_t i=0;
	if(num==1)
	{
		Objects[i].x=10;
		Objects[i].y=40;
		Objects[i].ID=Pooter_Init(Objects[i].x,Objects[i].y);
		Pooter_Get_Logic(&Objects[i]);
	
		
	}
	if(num==0)
	{
		Objects[i].x=10;
		Objects[i].y=10;
		Objects[i].ID=Chaser_Init(Objects[i].x,Objects[i].y);
		Chaser_Get_Logic(&Objects[i]);
	}
	
}



