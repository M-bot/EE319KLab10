#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#define PI 3.141592654
#include "Rooms.h"
#include "Shot.h"
#include "SoundController.h"

#define LEFT -1;
#define STAY 0;
#define RIGHT 1;
//17x20
const unsigned short Character[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0841, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x94B8, 0x94B8, 0x94B8, 0xB5BD, 0xBDDE, 0x0000, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDFE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xBDFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDFE, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xE716, 0xBDFD, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE736, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xE6F6, 0xBDFD, 0xBDDE, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE716, 0x0000, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xE6F6, 0xE6F6, 0xE6F6,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE6F6, 0xE6F6, 0xE6F6, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x10A2,
 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x10A2, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE,
 0xFFDF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xFFDF, 0x1082, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0x0862, 0x18C3,
 0x9CF9, 0xAD5B, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BE, 0xB5BE, 0xAD5B, 0x2104,
 0xFFFF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDFE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0xA53B, 0xB59C, 0xB59C, 0xAD7C, 0xAD7C, 0xAD7C, 0xB59C, 0xB59C, 0xB59C, 0x18C3,
 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};


const unsigned short Character_Firing[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0841, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x94B8, 0x94B8, 0x94B8, 0xB5BD, 0xBDDE, 0x0000, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDFE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xBDFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDFE, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xE716, 0xBDFD, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE736, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xE6F6, 0xBDFD, 0xBDDE, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE716, 0x0000, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xE6F6, 0xE6F6, 0xE6F6,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE6F6, 0xE6F6, 0xE6F6, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000, 0xAD7C,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0x0862, 0x18C3,
 0x9CF9, 0xAD5B, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BE, 0xB5BE, 0xAD5B, 0x2104,
 0xFFFF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDFE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0xA53B, 0xB59C, 0xB59C, 0xAD7C, 0xAD7C, 0xAD7C, 0xB59C, 0xB59C, 0xB59C, 0x18C3,
 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};

const unsigned short Character_Move_1[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0841, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x94B8, 0x94B8, 0x94B8, 0xB5BD, 0xBDDE, 0x0000, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xBDFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDFE, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xE716, 0xBDFD, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE736, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xE6F6, 0xBDFD, 0xBDDE, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE716, 0x0000, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xE6F6, 0xE6F6, 0xE6F6,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE6F6, 0xE6F6, 0xE6F6, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x10A2,
 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x10A2, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE,
 0xFFDF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xFFDF, 0x1082, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0x0862, 0x18C3,
 0x9CF9, 0xAD5B, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BE, 0xB5BE, 0xAD5B, 0x2104,
 0xFFFF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDFE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0xA53B, 0xB59C, 0xB59C, 0xAD7C, 0xAD7C, 0xAD7C, 0xB59C, 0xB59C, 0xB59C, 0x18C3,
 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};

const unsigned short Character_Move_2[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0841, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x94B8, 0x94B8, 0x94B8, 0xB5BD, 0xBDDE, 0x0000, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDFE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xBDDE, 0x0862, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDFE, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xE716, 0xBDFD, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE736, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xE6F6, 0xBDFD, 0xBDDE, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xE716, 0x0000, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xE6F6, 0xE6F6, 0xE6F6,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xE6F6, 0xE6F6, 0xE6F6, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x0000, 0x0000,
 0x0000, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0xBDFE, 0x0000, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE, 0x10A2,
 0x0000, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x10A2, 0x0000, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C, 0xBDDE,
 0xFFDF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xFFDF, 0x1082, 0x0000, 0xBDDE, 0x0862, 0x0000, 0xAD7C,
 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0x0862, 0x18C3,
 0x9CF9, 0xAD5B, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xB5BE, 0xB5BE, 0xAD5B, 0x2104,
 0xFFFF, 0x1082, 0x0000, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDFE, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xAD7C, 0xBDDE, 0xBDDE, 0xB5BD, 0xB5BD, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0x0862, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0861, 0xA53B, 0xB59C, 0xB59C, 0xAD7C, 0xAD7C, 0xAD7C, 0xB59C, 0xB59C, 0xB59C, 0x18C3,
 0x0861, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x1082, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};





uint32_t Damage; 
uint32_t Fire_Rate;  //# Times per Second
uint32_t Speed;      //Pixels per second if held down
uint8_t Max_Health; //Multiples of two to correspond to half hearts
uint8_t Current_Health;  //""
uint32_t Shot_Speed;      // Tears pixels per second from when they are created
uint8_t Current_x;
uint8_t Current_y;
uint8_t Width;
uint8_t Height;
uint8_t ID;
uint8_t Last_x;
uint8_t Last_y;
uint8_t Range;
uint8_t Current_Fire_Rate;
uint32_t Score;

void Character_Init(void)
{
		Score=0;
		Range=30;
		Damage = 2;
		Fire_Rate = 5;
		Current_Fire_Rate=0;
		Speed = 3;
		Max_Health = 6;
		Current_Health =6;
	  Shot_Speed = 3;
		Width =17;
		Height =20;
	  Current_x = 61;
		Current_y = 30;
		ID = AddSprite(Character,Width,Height,Current_x,Current_y);
	  DrawHearts(Current_Health,Max_Health);
	//	UpdateHeart(Max_Health,Current_Health);
	
}

uint8_t Check_Collision(uint8_t test_x, uint8_t test_y, uint8_t test_width, uint8_t test_height)
{
	uint8_t t1=0;
	uint8_t t2=0;
	for(int i=0;i<Width;i++)
		for(int x =0;x<test_width;x++)
			if((i+Current_x)==(x+test_x))
			{
				t1=1;
				i=Width;
				x=test_width;
			}
	for(int j=0;j<Height;j++)
		for(int y =0;y<test_height;y++)
			if((j+Current_y)==(y+test_y))
			{
				t2=1;
				j=Height;
				y=test_height;
				
			}
	return (t1 && t2);
}
	
void Move(int8_t x,int8_t y,uint8_t move_checker)
{
	
	if( (Current_x+Width + x*Speed)<=140 && (int8_t)(Current_x + x*Speed)>=0)
	{
		/*if(x!=0 && y!=0)
		{
			Current_x= Current_x*10 +(int8_t)((x*Speed*10)/(int8_t)sqrt(2));
			Current_x = Current_x/10 + (Current_x%10)/5;
		}
		else*/
		Last_x= Current_x;
		Current_x += x*Speed;
	}
	if( (Current_y+Height + y*Speed)<=80 && (int8_t)(Current_y + y*Speed)>=1)
	{
		/*if(x!=0 && y!=0)
		{
			Current_y= Current_y*10 +(int8_t)((y*Speed*10)/(int8_t)sqrt(2));
			Current_y= Current_y/10 + (Current_y%10)/5;
		}
		else*/
		Last_y=Current_y;
		Current_y += y*Speed;
		
	}
	//if(x!=0 && y!=0)
	UpdateSprite(ID,Current_x,Current_y);
	
}
void Place(int8_t x,int8_t y)
{
	UpdateSprite(ID,x,y);
	Last_x=Current_x;
	Last_y=Current_y;
	Current_x=x;
	Current_y=y;
}
void Damage_Player(void)
{
	//for(uint32_t i;i<20;i++)
		Sound_Send(2);
		Current_Health--;
		UpdateHeart(Max_Health,Current_Health);
	
	if(Current_Health==0)
	{
		RemoveSprite(ID);
		//UpdateHeart(6,0);
		Output_Clear();
		LCD_OutDec(Score);
		while(1);
	}
	Sound_Stop();
}
uint8_t Get_Last_x(void)
{
	return Last_x;
}
uint8_t Get_Last_y(void)
{
	return Last_y;
}
uint8_t Get_x(void)
{
	return Current_x;
}
uint8_t Get_y(void)
{
	return Current_y;
}
uint8_t Fire_Shot(void)
{
	if(Fire_Rate==Current_Fire_Rate)
	{
	Current_Fire_Rate=0;
	 return 1;
		
	}
	Current_Fire_Rate++;
	if(Current_Fire_Rate==1)
	{
	RemoveSprite(ID);
	ID=AddSprite(Character,Width,Height,Current_x,Current_y);
	}
	return 0;
	
}
void Create_Shot(int8_t xdir,int8_t ydir,objects_t *o)
{
	//for(uint8_t i;i<20;i++)
		Sound_Send(3);
	uint8_t x =  Current_x;
	uint8_t y = Current_y;
	if(xdir==-1 & ydir ==1)
	{
		x-=4;
		y+=Height+2;
	}
	else if(xdir==-1 & ydir ==0)
	{
		x-=4;
		y+=(Height/2);
	}
	else if(xdir==-1 & ydir ==-1)
	{
		x-=4;
		y-=4;
	}
	else if(xdir==0 & ydir ==-1)
	{
		x+=Width/2;
		y-=4;
	}
	else if(xdir==0 & ydir ==1)
	{ x+=Width/2;
		y+=Height+4;
	}
	else if(xdir==1 & ydir ==1)
	{
		x+=Width;
		y+=Height+4;
	}
	else if(xdir==1 & ydir ==0)
	{ x+=Width;
		y+=Height/2;
	}
	else if(xdir==1 & ydir ==-1)
	{	x+=Width;
		y-=4;
	}
	o->x=x;
	o->y=y;
  o->ID=Shot_Init(x,y);
	o->w=4;
	o->h=4;
	o->veli=Shot_Speed*(xdir);
	o->velj=Shot_Speed*(ydir);
	o->react=3;
	o->moves=1;
	o->fires=0;
	o->Changes_Sprites=0;
	o->Current_Health=1;
	o->Move_Logic=3;
	o->Damage_To_Deal=Damage;
	o->Player=1;
	o->xo=x;
	o->yo=y;
	o->rangex=Range;
	o->rangey=Range;
	RemoveSprite(ID);
	ID=AddSprite(Character_Firing,Width,Height,Current_x,Current_y);
	Sound_Stop();
}
uint8_t Get_Width(void)
{
	return Width;
}
uint8_t Get_Height(void)
{
	return Height;
}
void Update_Stats(uint8_t code, uint8_t delta)
	//1=damage 2=fire_rate 3=Speed 4=Shot_Speed 5=Range 6=Max_Health 7=Current_Health
{
	switch(code) {
		case 1:
			Damage+=delta;
			break;
		case 2:
			Fire_Rate+=delta;
			break;
		case 3:
			Speed+=delta;
			break;
		case 4:
			Shot_Speed+=delta;
			break;
		case 5:
			Range+=delta;
			break;
		case 6:
			Max_Health+=delta;
			UpdateHeart(Max_Health,Current_Health);
			break;
		case 7:
			Current_Health+=delta;
			UpdateHeart(Max_Health,Current_Health);
			break;
	}

}
void Update_Damage(int8_t delta)
{
	Damage+=delta;
}
void Update_Fire_Rate(int8_t delta)
{
	Fire_Rate+=delta;
}
void Update_Speed(int8_t delta)
{
	Speed+=delta;
}
void Update_Shot_Speed(int8_t delta)
{
	Shot_Speed+=delta;
}
void Update_Range(int8_t delta)
{
	Range+=delta;
}
void Update_Max_Health(int8_t delta)
{
	Max_Health+=delta;
}
void Update_Current_Health(int8_t delta)
{
	Current_Health+=delta;
}
void Sprite_Move_1(void)
{
	RemoveSprite(ID);
	ID=AddSprite(Character_Move_1,Width,Height,Current_x,Current_y);
	
}
void Sprite_Move_2(void)
{
	RemoveSprite(ID);
	ID=AddSprite(Character_Move_2,Width,Height,Current_x,Current_y);
	
}
void Sprite_Still(void)
{
	RemoveSprite(ID);
	ID=AddSprite(Character,Width,Height,Current_x,Current_y);
}
void Update_Score(uint32_t delta)
{
	Score+=delta;
}
