#include <stdint.h>
#include "tm4c123gh6pm.h"

//swtich init
//input none
//output none
void Switch_Init(void);


//movement sensor in
//returns point to array with x and y direction
void Mov_In(int8_t arr[2]);



//fire sensor in
//returns point to array with x and y direction
void Fire_In(int8_t *arr);
uint32_t Get_Data(void);