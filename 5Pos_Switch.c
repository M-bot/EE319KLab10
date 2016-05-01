#include <stdint.h>
#include "tm4c123gh6pm.h"

#define  Pins 0x1F  

//5 Position intialization
//Intializes ports B and D for Movement and Shooting 
//Pin0=LEFT,Pin1=UP,Pin2=DOWN,Pin3=RIGHT,Pin4=PRESSED
void Switch_Init(void)
{
	int delay=0;
	SYSCTL_RCGCGPIO_R |= 0x0A;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_DIR_R &= ~Pins;
	GPIO_PORTD_DIR_R &= ~Pins;
	GPIO_PORTB_DEN_R |= Pins;
	GPIO_PORTD_DEN_R |= Pins;
	GPIO_PORTB_AFSEL_R &= ~Pins;
	GPIO_PORTD_AFSEL_R &= ~Pins;

}
//checks movement swtich for position and returns corresponding x and y coordinate
//[{-1,0,1},{-1,0,1}] [x,y]  -1 =down or left, 0= neither direction 1= right or up
void Mov_In(uint8_t arr[2])
{
	int Data = ~GPIO_PORTB_DATA_R;
  arr[0] =    ((Data&(0x08))>>3) + ((Data&(0x01))*-1);
	arr[1] =    (((Data&(0x02))>>1)*(-1)) + (((Data&(0x04))>>2));
}

//checks firing swtich for position and returns corresponding x and y coordinate
//[{-1,0,1},{-1,0,1}]  -1 =down or left, 0= neither direction 1= right or up
void Fire_In(uint8_t arr[2])
{
	int Data = ~GPIO_PORTD_DATA_R;
  arr[0] =    ((Data&(0x08))>>3) + ((Data&(0x01))*-1);
	arr[1] =    (((Data&(0x02))>>1)*(-1)) + (((Data&(0x04))>>2));
}
	