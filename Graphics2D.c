#include <stdint.h>
#include "Graphics2D.h"
#include "ST7735.h"
#include "Timer1.h"
#include "tm4c123gh6pm.h"
#include "ADC.h"
#include "Map.h"

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

#define BLACK 0x0000
#define DARK_GRAY 0x18C3
#define GRAY 0x39C7
#define LIGHT_GRAY 0x738E
#define WHITE 0xFFFF

#define MAX_SPRITES 100

#define UPDATE_DOOR 0x1
#define UPDATE_HEART 0x2
#define UPDATE_MAP 0x4

#define DIMMER_PIN 0x20

uint16_t pixels[ROOM_WIDTH*ROOM_HEIGHT];
// Change to vector later
Sprite sprites[MAX_SPRITES];
uint8_t ssize = 0;
uint32_t sunique = 1;
uint8_t updatestatus = 0;
uint8_t door = 0;
uint8_t max_hearts = 0;
uint8_t cur_hearts = 0;

uint16_t duty = 100;
uint16_t cur = 0;
void Dimmer(void) {
	if(cur == duty) {
		GPIO_PORTB_DATA_R &= ~DIMMER_PIN;
	}
	if(cur == 100) {
		cur = 0;
		GPIO_PORTB_DATA_R |= DIMMER_PIN;
	}
	cur++;
}

// Initializes display and draws initial images
void Graphics2DInit(void) {
  // Inititalize the display
  ST7735_InitR(INITR_REDTAB);
  // Set screen to landscape
  ST7735_SetRotation(1);
  


	
	int delay=0;
	SYSCTL_RCGCGPIO_R |= 0x02;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_DIR_R |= DIMMER_PIN;
	GPIO_PORTB_DEN_R |= DIMMER_PIN;
	GPIO_PORTB_AFSEL_R &= ~DIMMER_PIN;
	GPIO_PORTB_DATA_R |= 0x20;
	
	Timer1_Init(Dimmer, 80000000/10000);
}

void InitDraw(void) {
	Output_Clear();
	  // Draw the HUD
  ST7735_FillRect(0,0,WIDTH,HUD_HEIGHT,DARK_GRAY);
  
  DrawMap();
  
  DrawBorderRect(ITEM_X,ITEM_Y,ITEM_SIZE,ITEM_SIZE,GRAY,0);
  DrawBorderRect(ARROW_X,ITEM_Y,ITEM_SIZE,ITEM_SIZE,GRAY,0);
  
  //DrawHearts(6,12);
  // Draw the four corners of the wall
  DrawImageScreen(0,HUD_HEIGHT+WALL,corner_i,WALL,WALL,0);
  DrawImageScreen(WIDTH-WALL,HUD_HEIGHT+WALL,corner_i,WALL,WALL,1);
  DrawImageScreen(WIDTH-WALL,HEIGHT,corner_i,WALL,WALL,2);
  DrawImageScreen(0,HEIGHT,corner_i,WALL,WALL,3);
  // Draw the four walls
  for(int x = 0; x < 4; x++) {
    DrawWall(x,1);
  }
}

// Loads the given sprite data into an available slot and returns its unique identifier
uint8_t AddSprite(const unsigned short * image, uint8_t width, uint8_t height, uint8_t initialx, uint8_t initialy) {
	if(ssize == MAX_SPRITES)
		return -1;
	int x;
	for(x = 0; x < MAX_SPRITES; x++) {
		if(sprites[x].width == 0) {
			break;
		}
	}
	sprites[x].image = image;
	sprites[x].width = width;
	sprites[x].height = height;
	sprites[x].x = initialx;
	sprites[x].y = initialy;
	sprites[x].unique = GetNextUnique();
	ssize++;
	return sprites[x].unique;
}
// Returns the next available unique to avoid conflicts
uint8_t GetNextUnique(void) {
	uint32_t n = 0;
	for(int x = 0; x < MAX_SPRITES; x++) {
		if(n == sprites[x].unique) {
			n++;
			x = -1;
		}
	}
	return n;
}

// Updates the positional data of a given sprite from a unique value
void UpdateSprite(uint8_t unique, uint8_t screenx, uint8_t screeny) {
	for(int x = 0; x < MAX_SPRITES; x++) {
		if(sprites[x].unique == unique) {
			sprites[x].x = screenx;
			sprites[x].y = screeny;
			return;
		}
	}
}

// Removes the from rendering the given sprite from a unique value
uint8_t RemoveSprite(uint8_t unique) {
	for(int x = 0; x < MAX_SPRITES; x++) {
		if(sprites[x].unique == unique) {			
			sprites[x].image = 0;
			sprites[x].width = 0;
			sprites[x].height = 0;
			sprites[x].x = 0;
			sprites[x].y = 0;
			sprites[x].unique = 0;
			ssize--;
			return 0;
		}
	}
	return 1;
}
// Updates doors, must be given a flag where every 2 bits are each doors data
// the least significant of which are the top door and then in a clockwise fashion 
// to the left door as the most significant
void UpdateDoor(uint8_t d) {
	door = d;
	updatestatus |= UPDATE_DOOR;
}

// Updates hearts, both max and current our in half-heart units
// The max number of half hearts displayable is 24
void UpdateHeart(uint8_t max, uint8_t current) {
	max_hearts = max;
	cur_hearts = current;
	updatestatus |= UPDATE_HEART;
}

void UpdateMap(void) {
	updatestatus |= UPDATE_MAP;
}

// Checks the status flag to see if there is any rendering data that
// needs to be pushed to the screen
void CheckUpdates(void) {
	if((updatestatus & UPDATE_DOOR) == UPDATE_DOOR) {
		for(int x = 0; x < 4; x++) {
			// Add current wall/door status to avoid rendering all walls on update
			DrawWall(x,door & 0x3);
			door >>= 2;
		}
		updatestatus &= ~UPDATE_DOOR;
	}
	if((updatestatus & UPDATE_HEART) == UPDATE_HEART) {
		DrawHearts(cur_hearts,max_hearts);
		updatestatus &= ~UPDATE_HEART;
	}
	if((updatestatus & UPDATE_MAP) == UPDATE_MAP) {
		DrawMap();
	}
}

// Draws all the sprites in linear fashion, does not support z levels
void DrawSprites(void) {
	for(int x = 0; x < MAX_SPRITES; x++) {
		if(sprites[x].width == 0) continue;
		DrawImage(sprites[x].x,sprites[x].y,sprites[x].image,sprites[x].width,sprites[x].height);
	}
}

// Draws a string in the given color, this method is different than the ST7735
// equivalent because it does not verify the text is on screen
void DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  while(*pt){
    ST7735_DrawCharS(x, y, *pt, textColor, textColor, 1);
    pt++;
    x = x+6;
  }
}

// Draws a non-filled rectangle
void DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  ST7735_DrawFastVLine(x,y,h,color);
  ST7735_DrawFastVLine(x+w-1,y,h,color);
  ST7735_DrawFastHLine(x+1,y,w-2,color);
  ST7735_DrawFastHLine(x+1,y+h-1,w-2,color);
}

// Draws a filled rectangle with a 1 pixel border
void DrawBorderRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color1,uint16_t color2) {
  ST7735_FillRect(x,y,w,h,color1);
  DrawRect(x,y,w,h,color2);
}

const uint16_t map_colors[8] = {DARK_GRAY,DARK_GRAY,DARK_GRAY,DARK_GRAY,GRAY,WHITE,LIGHT_GRAY,WHITE};
const uint16_t map_bcolors[8] = {DARK_GRAY,DARK_GRAY,DARK_GRAY,DARK_GRAY,BLACK,BLACK,BLACK,BLACK};
void DrawMap(void) {
	for(int x = 0; x < MAP_DATA_SIZE; x++) {
		for(int y = 0; y < MAP_DATA_SIZE; y++) {
			uint8_t data = Get_Map_Data(x,y);
			DrawBorderRect(MAP_CENTER_X-(MAP_SIZE+MAP_SIZE*2*(x-MAP_DATA_SIZE/2)),MAP_CENTER_Y-(MAP_SIZE/2+MAP_SIZE*(y-MAP_DATA_SIZE/2)),MAP_SIZE*2,MAP_SIZE,map_colors[data],map_bcolors[data]);
		}
	}
}

// Draws half a heart
// Saves 56 bytes of ROM by combining a full heart and empty heart
// Costs 198 bytes of transfer to LCD
void DrawHalfHeart(uint16_t x, uint16_t y) {
  for(int r = 0; r < 7; r++) {
    for(int c = 0; c < 8; c++) {
      ST7735_DrawPixel(x+c,y-r,c > 3 ? heartempty_i[c+r*8] : heartfull_i[c+r*8]);
    }
  }
}

// Draws the life meter
void DrawHearts(uint8_t maxhealth, uint8_t health) {
	ST7735_FillRect(HEART_X,HEART_Y,54,16,DARK_GRAY);
  for(int l = 0; l < 2; l++) {
    for(int h = 0; h < 12 && h < health-l*12; h++) {
      if(h % 2 == 0) {
        DrawImageScreen(HEART_X+h/2*9,HEART_Y+7+8*l, h >= maxhealth - l * 12 ? heartempty_i : heartfull_i,8,7,0);
      }
      if(maxhealth % 2 == 1 && h == maxhealth-1-l*12) {
        DrawHalfHeart(HEART_X+h/2*9,HEART_Y+7+8*l);
      }
    }
  }
}


// Draws any of the four walls, with or without a door
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
  
  // Need to seperate these
  if(door >= 1) {
		switch(rot) {
			case 1:
				DrawImageScreen(WIDTH-20,HEIGHT-ROOM_HEIGHT/2,door == 1 ? door_i : door_i,20,20,1);
				break;
			case 2:
				DrawImageScreen(WIDTH/2-WALL,HEIGHT,door == 1 ? door_i : door_i,20,20,2);
				break;
			case 3:
				DrawImageScreen(0,HEIGHT-ROOM_HEIGHT/2,door == 1 ? door_i : door_i,20,20,3);
				break;
			default:
				DrawImageScreen(WIDTH/2-WALL,HEIGHT-ROOM_HEIGHT,door == 1 ? door_i : door_i,20,20,0);
				break;
		}
  }
}

// Draws the background
void ClearBuffer(void) {
  // Clears to black, should clear to current background
  for(int p = 0; p < ROOM_WIDTH*ROOM_HEIGHT; p++) {
    pixels[p] = 0x424F;//bg[p%10 + p/ROOM_WIDTH*10%100];
  }
}

// Draws everything that needs to be drawn
void Render(void) {
	duty = ADC_In() * 100 / 0xFFF;
	if(duty < 1) duty = 1;
	if(duty > 99) duty = 99;
  ClearBuffer();
	DrawSprites();
	CheckUpdates();
  ST7735_DrawBitmap(WALL,HEIGHT-WALL,pixels,ROOM_WIDTH,ROOM_HEIGHT);
}

// Draws an image to the room buffer
void DrawImage(uint16_t x, uint16_t y, const unsigned short * image, uint16_t w, uint16_t h) {
  // Perform clipping on the image so it fits in the room
  int16_t hh = h,ww = w;
  if((y+h) >= ROOM_HEIGHT)
    hh = ROOM_HEIGHT - y;
  if((x+w) >= ROOM_WIDTH)
    ww = ROOM_WIDTH - x;
  y = ROOM_HEIGHT - y;
  // Draw image to buffer
  for(int r = 0; r < hh; r++) {
    for(int c = 0; c < ww; c++) {
      // Use 0xFFFF as transparency color
      if(image[(hh-r-1)*w+c] == 0xFFFF) continue; 
      pixels[(y-r)*ROOM_WIDTH+x+c] = image[(hh-r-1)*w+c];
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
