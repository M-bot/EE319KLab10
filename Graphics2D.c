#include <stdint.h>
#include "Graphics2D.h"
#include "ST7735.h"
#include "Timer0.h"

const unsigned short issac[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x2946, 0x8416, 0x0000, 0x0000, 0x0000, 0x9CF8, 0x2946, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x420A, 0xB59D, 0x31A8, 0x2947, 0x422B, 0xC63F,
 0x420A, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x39A9, 0xC5FF, 0xC61F, 0xC5FF,
 0xC61F, 0xC61F, 0x39A9, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x420A, 0xCE5F,
 0xC63F, 0xC63F, 0xC63F, 0xCE5F, 0x420A, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,
 0x10A3, 0x7BD4, 0x7394, 0x7393, 0x7393, 0x7BB3, 0x0000, 0x0000, 0x0862, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
 0xAD7C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xAD7C, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0x0000, 0x41EA, 0x8435, 0x9478, 0x94B8, 0x9CF9, 0xA4F9, 0xA4F9, 0x9CD9, 0x9499, 0x7394, 0x3188, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x5AAA, 0xB5BE, 0x9CF9, 0x8415, 0x8C37, 0x8C37, 0x8C37, 0x8C55, 0xAD5D, 0xAD5B, 0x4A67, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x4206, 0xDEB8, 0xC61F, 0x422C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6B52, 0xCE5F,
 0xEF17, 0x0861, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x4A6C, 0x9491, 0xE716, 0xE73A, 0x5AC8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x840E, 0xEF59, 0xF736, 0xB596, 0x4A6D, 0x0000, 0xFFFF, 0x0020, 0xBDBE, 0xAD76, 0xAD2F, 0xA510, 0x630B, 0x2967, 0x2126, 0x2126,
 0x2126, 0x2967, 0x738C, 0xAD30, 0xAD2F, 0xB5B9, 0xAD3B, 0x0000, 0xFFFF, 0x0020, 0xBDBE, 0x528D, 0x0000, 0x0000, 0x6B31, 0xC63F,
 0xBDFF, 0xC61F, 0xC5FF, 0xBDBF, 0x4A6C, 0x0000, 0x0000, 0x7392, 0xAD5C, 0x0000, 0xFFFF, 0x0020, 0xB5BE, 0xB5B9, 0x9492, 0x0000,
 0x6B51, 0xC61F, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDF, 0xBDDA, 0x94B2, 0x0020, 0x6B72, 0xAD7C, 0x0000, 0xFFFF, 0x0000, 0xB59E, 0xDEDF,
 0xCE7B, 0x3187, 0x7BD4, 0xBDBF, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDDE, 0xDEFF, 0xD6BB, 0x39C8, 0x8415, 0xAD7B, 0x0000, 0xFFFF, 0x0000,
 0xAD5C, 0xC61E, 0xC63F, 0xAD5D, 0xBDFE, 0xBDBE, 0xB5BD, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDFE, 0xBDDF, 0xAD5C, 0xB5BE, 0x8415, 0x0000,
 0xFFFF, 0x0000, 0x0000, 0x8C56, 0xC5FF, 0xBDDE, 0xBDDE, 0xBDBE, 0xBDBE, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDDE, 0xBDDE, 0xC5FE, 0x422B,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x94B9, 0xC5FF, 0xBDDE, 0xBDDE, 0xBDBE, 0xBDBE, 0xBDBE, 0xBDDE, 0xBDDE, 0xBDDE,
 0x7BB3, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xB59D, 0xC5FF, 0xC63F, 0xC61F, 0xC63F, 0xC63F, 0xBDFF,
 0xC5FF, 0x8414, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x1082, 0x1083, 0x1083, 0x1083, 0x1082,
 0x1083, 0x1083, 0x1083, 0x10A3, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};

const unsigned short bg[] = {
 0x31EC, 0x4A8F, 0x428F, 0x428F, 0x29CC, 0x52F1, 0x29AC, 0x31ED, 0x3A2D, 0x320D, 0x214A, 0x52F1, 0x29CC, 0x4AB0, 0x298B, 0x216A,
 0x216B, 0x29AC, 0x3A2E, 0x320D, 0x4AB0, 0x3A2D, 0x29CC, 0x31ED, 0x194A, 0x320D, 0x424E, 0x426F, 0x29AC, 0x31EC, 0x216B, 0x218B,
 0x29AB, 0x29CC, 0x4A8F, 0x52F1, 0x4AD0, 0x29AC, 0x216B, 0x320D, 0x29AC, 0x31CC, 0x4AB0, 0x4AD0, 0x4AB0, 0x4AB0, 0x31EC, 0x216B,
 0x426F, 0x52D0, 0x426F, 0x214A, 0x3A4E, 0x31ED, 0x31CC, 0x320D, 0x426E, 0x3A2E, 0x4A8F, 0x320D, 0x320D, 0x3A4E, 0x3A2E, 0x428F,
 0x29AC, 0x3A2E, 0x29CC, 0x3A4E, 0x320D, 0x4AD0, 0x424E, 0x426E, 0x52F1, 0x3A4E, 0x428F, 0x426F, 0x29CC, 0x426F, 0x194A, 0x218B,
 0x426F, 0x298B, 0x31ED, 0x426F, 0x4AB0, 0x52D0, 0x4AB0, 0x424E, 0x216B, 0x4AD0, 0x29CC, 0x216A, 0x428F, 0x218B, 0x216B, 0x214A,
 0x31CC, 0x31ED, 0x426F, 0x4AD0,

};

const unsigned short corner_i[] = {
 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x29CB, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x29CB, 0x29CB,
 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270,
 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB,
 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB,
 0x29CB, 0x29CB, 0x29CB, 0x29CB,

};

const unsigned short wall_i[] = {
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB,
 0x29CB, 0x29CB, 0x29CB, 0x29CB,

};

const unsigned short door_i[] = {
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB,
 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB,
 0x29CB, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x29CB,
 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB,
 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270,
 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270, 0x4270,
 0x4270, 0x4270, 0x4270, 0x4270, 0x29CB, 0x4270, 0x4270, 0x4270, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB,
 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB,
 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB, 0x29CB,


};


const unsigned short heartfull_i[] = {
 0x18C3, 0x18C3, 0x18C3, 0x0000, 0x0000, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x0000, 0x0014, 0x0014, 0x0000, 0x18C3, 0x18C3,
 0x18C3, 0x0000, 0x001F, 0x001F, 0x001F, 0x0014, 0x0000, 0x18C3, 0x0000, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x0014, 0x0000,
 0x0000, 0xF79E, 0x001F, 0x001F, 0x001F, 0x001F, 0x0014, 0x0000, 0x0000, 0xF79E, 0x001F, 0x0000, 0x001F, 0x001F, 0x0014, 0x0000,
 0x18C3, 0x0000, 0x0000, 0x18C3, 0x0000, 0x0000, 0x0000, 0x18C3,

};


const unsigned short heartempty_i[] = {
 0x18C3, 0x18C3, 0x18C3, 0x0000, 0x0000, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x0000, 0x18C3, 0x18C3, 0x0000, 0x18C3, 0x18C3,
 0x18C3, 0x0000, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x0000, 0x18C3, 0x0000, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x0000,
 0x0000, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x18C3, 0x0000, 0x0000, 0x18C3, 0x18C3, 0x0000, 0x18C3, 0x18C3, 0x18C3, 0x0000,
 0x18C3, 0x0000, 0x0000, 0x18C3, 0x0000, 0x0000, 0x0000, 0x18C3,

};

#define WIDTH 160
#define HEIGHT 128
#define ROOM_WIDTH 140
#define ROOM_HEIGHT 80 
#define HUD_HEIGHT (HEIGHT-ROOM_HEIGHT-WALL*2)
#define HEART_X (WIDTH-54)
#define HEART_Y (HUD_HEIGHT)/2-8
#define WALL 10
#define ITEM_SIZE (HUD_HEIGHT*5/8)
#define ITEM_Y (HUD_HEIGHT*3/16)
#define ITEM_X (HEART_X-ITEM_SIZE-5)
#define ARROW_X (ITEM_X-ITEM_SIZE-5)
#define MAP_SIZE ((HUD_HEIGHT-8)/5)
#define MAP_CENTER_X (ARROW_X/2)
#define MAP_CENTER_Y (HUD_HEIGHT/2)

#define DARK_GRAY 0x18C3
#define GRAY 0x39C7
#define LIGHT_GRAY 0x738E
#define WHITE 0xFFFF

uint16_t pixels[ROOM_WIDTH*ROOM_HEIGHT];

void Graphics2DInit(void) {
  // Inititalize the display
  ST7735_InitR(INITR_REDTAB);
  // Set screen to landscape
  ST7735_SetRotation(1);
  
  // Draw initial screen
  // Clear the buffer to the default background
  ClearBuffer();
  // Draw the HUD
  ST7735_FillRect(0,0,WIDTH,HUD_HEIGHT,DARK_GRAY);
  
  DrawMap();
  
  DrawBorderRect(ITEM_X,ITEM_Y,ITEM_SIZE,ITEM_SIZE,GRAY,0);
  DrawBorderRect(ARROW_X,ITEM_Y,ITEM_SIZE,ITEM_SIZE,GRAY,0);
  
  DrawHearts(7,24);
  // Draw the four corners of the wall
  DrawImageScreen(0,HUD_HEIGHT+WALL,corner_i,WALL,WALL,0);
  DrawImageScreen(WIDTH-WALL,HUD_HEIGHT+WALL,corner_i,WALL,WALL,1);
  DrawImageScreen(WIDTH-WALL,HEIGHT,corner_i,WALL,WALL,2);
  DrawImageScreen(0,HEIGHT,corner_i,WALL,WALL,3);
  // Draw the four walls
  for(int x = 0; x < 4; x++) {
    DrawWall(x,1);
  }
  // Draw the room
  ST7735_DrawBitmap(WALL,HEIGHT-WALL,pixels,ROOM_WIDTH,ROOM_HEIGHT);
}

void DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  while(*pt){
    ST7735_DrawCharS(x, y, *pt, textColor, textColor, 1);
    pt++;
    x = x+6;
  }
}

void DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  ST7735_DrawFastVLine(x,y,h,color);
  ST7735_DrawFastVLine(x+w-1,y,h,color);
  ST7735_DrawFastHLine(x+1,y,w-2,color);
  ST7735_DrawFastHLine(x+1,y+h-1,w-2,color);
}

void DrawBorderRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1,uint16_t color2) {
  ST7735_FillRect(x,y,w,h,color1);
  DrawRect(x,y,w,h,color2);
}

// Fake map atm
void DrawMap(void) {
  // Center room is light gray
  DrawBorderRect(MAP_CENTER_X-MAP_SIZE,MAP_CENTER_Y-MAP_SIZE/2,MAP_SIZE*2,MAP_SIZE,LIGHT_GRAY,0);
  // Discovered rooms are gray
  DrawBorderRect(MAP_CENTER_X-MAP_SIZE*3,MAP_CENTER_Y-MAP_SIZE/2,MAP_SIZE*2,MAP_SIZE,GRAY,0);
  DrawBorderRect(MAP_CENTER_X-MAP_SIZE,MAP_CENTER_Y+MAP_SIZE/2,MAP_SIZE*2,MAP_SIZE,GRAY,0);
  DrawBorderRect(MAP_CENTER_X+MAP_SIZE,MAP_CENTER_Y-MAP_SIZE*3/2,MAP_SIZE*2,MAP_SIZE,GRAY,0);
  // Current room is white
  DrawBorderRect(MAP_CENTER_X+MAP_SIZE,MAP_CENTER_Y-MAP_SIZE/2,MAP_SIZE*2,MAP_SIZE,WHITE,0);
}

// Saves 56 bytes of ROM by combining a full heart and empty heart
// Costs 198 bytes of transfer to LCD
void DrawHalfHeart(uint16_t x, uint16_t y) {
  for(int r = 0; r < 7; r++) {
    for(int c = 0; c < 8; c++) {
      ST7735_DrawPixel(x+c,y-r,c > 3 ? heartempty_i[c+r*8] : heartfull_i[c+r*8]);
    }
  }
}

void DrawHearts(uint8_t life, uint8_t max) {
  for(int l = 0; l <= 2; l++) {
    for(int h = 0; h < 12 && h < max-l*12; h++) {
      if(h % 2 == 0) {
        DrawImageScreen(HEART_X+h/2*9,HEART_Y+7+8*l,h>life-l*12 ? heartempty_i : heartfull_i,8,7,0);
      }
      if(life % 2 == 1 && h == life-1-l*12) {
        DrawHalfHeart(HEART_X+h/2*9,HEART_Y+7+8*l);
      }
    }
  }
}


void DrawWall(uint8_t rot, uint8_t door) {
  if(rot == 0) {
    for(int x = WALL; x < WIDTH-WALL; x+=WALL) {
      DrawImageScreen(x,HUD_HEIGHT+WALL,wall_i,WALL,WALL,0);
    }
  }
  
  if(rot == 1) {
    for(int x = HEIGHT-ROOM_HEIGHT; x < HEIGHT; x+=WALL) {
      DrawImageScreen(WIDTH-WALL,x,wall_i,WALL,WALL,1);
    }
  }
  
  if(rot == 2) {
    for(int x = WALL; x < WIDTH-WALL; x+=WALL) {
      DrawImageScreen(x,HEIGHT,wall_i,WALL,WALL,2);
    }
  }
  
  if(rot == 3) {
    for(int x = HEIGHT-ROOM_HEIGHT; x < HEIGHT; x+=WALL) {
      DrawImageScreen(0,x,wall_i,WALL,WALL,3);
    }
  }
  
  
  if(door == 1) {
    // Change to a switch statement later
    if(rot == 0) {
      DrawImageScreen(WIDTH/2-WALL,HEIGHT-ROOM_HEIGHT,door_i,20,20,0);
    }
    
    if(rot == 1) {
      DrawImageScreen(WIDTH-20,HEIGHT-ROOM_HEIGHT/2,door_i,20,20,1);
    }
    
    if(rot == 2) {
      DrawImageScreen(WIDTH/2-WALL,HEIGHT,door_i,20,20,2);
    }
    
    if(rot == 3) {
      DrawImageScreen(0,HEIGHT-ROOM_HEIGHT/2,door_i,20,20,3);
    }
  }
}

void ClearBuffer(void) {
  // Clears to black, should clear to current background
  for(int p = 0; p < ROOM_WIDTH*ROOM_HEIGHT; p++) {
    pixels[p] = 0x424F;//bg[p%10 + p/ROOM_WIDTH*10%100];
  }
}

uint16_t cur;
void Render(void) {
  ClearBuffer();
  DrawImage(cur,cur,issac,18,21);
  ST7735_DrawBitmap(WALL,HEIGHT-WALL,pixels,ROOM_WIDTH,ROOM_HEIGHT);
  cur = (cur + 1) % (ROOM_HEIGHT-21);
}

void DrawImage(uint16_t x, uint16_t y, const uint16_t * image, uint16_t w, uint16_t h) {
  // Perform clipping on the image so it fits in the room
  int16_t hh = h,ww = w;
  if((y+h) >= ROOM_HEIGHT)
    hh = ROOM_HEIGHT - y;
  if((x+w) >= ROOM_WIDTH)
    ww = ROOM_WIDTH - x;
  
  // Draw image to buffer
  for(int r = 0; r < hh; r++) {
    for(int c = 0; c < ww; c++) {
      // Use 0xFFFF as transparency color
      if(image[r*w+c] == 0xFFFF) continue; 
      pixels[(y+r)*ROOM_WIDTH+x+c] = image[r*w+c];
    }
  }  
}

// Draws an image directly to the screen. If rotated (square images only) takes up a lot of time
void DrawImageScreen(uint16_t x, uint16_t y, const uint16_t * image, uint16_t w, uint16_t h, uint8_t rot) {
  // No rotation, draw to screen
  if(rot == 0) {
    ST7735_DrawBitmap(x,y,image,w,h);
    return;
  }
  // To rotate we need a square image
  if(w != h) return;
  
  // 90 degrees
  if(rot == 1) {
    for(int r = 0; r < h; r++) {
      for(int c = 0; c < w; c++) {
        ST7735_DrawPixel(x+r,y-c,image[(w - c - 1) + r*w]);
      }
    }
  }
  // 180 degrees
  if(rot == 2) {
    for(int r = 0; r < h; r++) {
      for(int c = 0; c < w; c++) {
        ST7735_DrawPixel(x+r,y-c,image[(w - r - 1) + (w - c - 1)*w]);
      }
    }
  }
  
  // 270 degrees
  if(rot == 3) {
    for(int r = 0; r < h; r++) {
      for(int c = 0; c < w; c++) {
        ST7735_DrawPixel(x+r,y-c,image[c+(w - r - 1)*w]);
      }
    }
  }
}  

  // This is to test a filter that replaces tabs with 2 spaces
