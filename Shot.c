#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#include "Rooms.h"
#define PI 3.141592654

#define LEFT -1;
#define STAY 0;
#define RIGHT 1;
//4x4

const unsigned short Shot[] = {
 0xFFFF, 0xBC8E, 0xBC8E, 0xFFFF, 0xBC8E, 0xFFFA, 0xF779, 0xBC8E, 0xBC8E, 0xF779, 0xF779, 0xBC8E, 0xFFFF, 0xBC8E, 0xBC8E, 0xFFFF,


};
const unsigned short Shot_E[] = {
 0xFFFF, 0x1074, 0x1074, 0xFFFF, 0x1074, 0xA4DF, 0x83BF, 0x1074, 0x1074, 0x83BF, 0x83BF, 0x1074, 0xFFFF, 0x1074, 0x1074, 0xFFFF,


};








//uint32_t Fire_Rate=0;  //# Times per Second
//uint32_t Speed=1;      //Pixels per second if held down
//uint8_t Max_Health=10; //Multiples of two to correspond to half hearts


uint8_t Shot_Init(uint8_t x,uint8_t y)
{
	uint8_t id = AddSprite(Shot,4,4,x,y);
//	Render();
	return(id);
	
}
uint8_t Shot_E_Init(uint8_t x, uint8_t y)
{
	return(AddSprite(Shot_E,4,4,x,y));
}