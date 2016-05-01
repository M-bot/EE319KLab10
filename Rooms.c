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
	uint8_t xo;
	uint8_t yo;
	int8_t rangex;  //range of shot
	int8_t rangey;  
	uint8_t Range;  //how many pixels do shots travel produced by this object
	uint8_t Fire_Rate;  //how often does it fire
	uint8_t Fire_Tick; //keeps track of Fire_Rate
	uint8_t Shot_Speed;
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
	uint8_t Stat_to_change; //1=damage 2=fire_rate 3=Speed 4=Shot_Speed 5=Range 6=Max_Health 7=Current_Health
	uint8_t Stat_delta;
};
typedef struct objects objects_t;

void Room_Init(uint8_t num,objects_t Objects[30])
{uint8_t i=0;
	if(num==1)
	{
		Rock_Get_Logic(&(Objects[i]));
		Objects[i].x=1;
		Objects[i].y=1;
		Objects[i].ID=Rock_Init(Objects[i].x,Objects[i].y);
		i++;
		Rock_Get_Logic(&(Objects[i]));
		Objects[i].x=140-Objects[i].w;
		Objects[i].y=80-Objects[i].h;
		Objects[i].ID=Rock_Init(Objects[i].x,Objects[i].y);
		i++;
		Rock_Get_Logic(&(Objects[i]));
		Objects[i].x=140-Objects[i].w;
		Objects[i].y=1;
		Objects[i].ID=Rock_Init(Objects[i].x,Objects[i].y);
		i++;
		Rock_Get_Logic(&(Objects[i]));
		Objects[i].x=1;
		Objects[i].y=80-Objects[i].h;
		Objects[i].ID=Rock_Init(Objects[i].x,Objects[i].y);
		i++;
		Objects[i].ID=Arrow_Right_Init();
		i++;
		
	
		
	}
	if(num==0)
	{
		Objects[i].x=10;
		Objects[i].y=10;
		Objects[i].ID=Chaser_Init(Objects[i].x,Objects[i].y);
		Chaser_Get_Logic(&Objects[i]);
		i++;
		
	}
	
}



