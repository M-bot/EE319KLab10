#include <stdint.h>
#include "Map.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "random.h"
#include "Graphics2D.h"
#include "tm4c123gh6pm.h"

uint8_t map[MAP_DATA_SIZE][MAP_DATA_SIZE]; 

 uint32_t RandomInteger(uint32_t n){
  return ((Random32()>>24)%n)+1; 
}
 

uint8_t decays[4];
int8_t dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
 
void Spread_Rooms(int8_t x, int8_t y, uint8_t first) {
	if(x < 0 || x > MAP_DATA_SIZE || y < 0 || y > MAP_DATA_SIZE) return;
	for(int c = 0; c < 4; c++) {
		uint8_t d = RandomInteger(4)-1;
		if(decays[d] != 0) {
			decays[d]--;
			uint8_t dx = x+dir[d][0];
			uint8_t dy = y+dir[d][1];
			if(dx < 0 || dx > MAP_DATA_SIZE || dy < 0 || dy > MAP_DATA_SIZE) continue;
			if(map[dy][dy] != 0) continue;
			Spread_Rooms(dx, dy, 0);
		}
	}
	map[y][x] = first ? 1 : RandomInteger(1)+2; // Change to actual number of possible rooms
}
 
void Map_Generate(void) {
	for(int y = 0; y < MAP_DATA_SIZE; y++) {
		for(int x = 0; x < MAP_DATA_SIZE; x++) {
			map[y][x] = 0;
		}
	}
	uint8_t center = MAP_DATA_SIZE/2;
	for(int c = 0; c < 4; c++) {
		decays[c] = RandomInteger(MAP_DATA_SIZE/2);
	}
	Spread_Rooms(center,center,1);
	for(int y = 0; y < MAP_DATA_SIZE; y++) {
		for(int x = 0; x < MAP_DATA_SIZE; x++) {
			if(map[y][x] > 0) {
				map[y][x] |= 0x80;//remove to make hidden
			}
		}
	}
	map[MAP_DATA_SIZE/2][MAP_DATA_SIZE/2] |= 0x60;
	DrawMap();
}

 
void Map_Init(uint64_t seed) {
	Random_Init(seed);	// As far as I can tell setting the seed doesn't really return very random results
	for(int x = 0; x < seed; x++) {
		Random();
	}
	Map_Generate();
}

uint8_t Get_Room_Data(uint8_t x, uint8_t y) {
	return map[y][x] & 0x1F;
}

uint8_t Get_Map_Data(uint8_t x, uint8_t y) {
	return map[y][x] >> 5;
}

void Set_Room(uint8_t x, uint8_t y, uint8_t discur) {
	UpdateMap();
	switch(discur) {
		case 0:
			map[y][x] |= 0x20;	// Current
			break;
		case 1:	
			map[y][x] &= ~0x20; // Remove current
			break;
		case 2:
			map[y][x] |= 0x40;	// Visited
			break;
		case 3:
			map[y][x] |= 0x80;	// Discovered
			break;
	}
}
uint8_t Get_Center(void)
{
	return MAP_DATA_SIZE/2;
}

uint32_t delay;
int main1(void) {
	Map_Init(1);
	ST7735_InitR(INITR_REDTAB);
	while(1) {
		while(delay++ < 1000000);
		Map_Generate();
		ST7735_SetCursor(0,0);
		for(int y = 0; y < MAP_DATA_SIZE; y++) {
			for(int x = 0; x < MAP_DATA_SIZE; x++) {
				if(map[y][x] == 1)
					ST7735_OutChar(map[y][x]);
				else if(map[y][x] != 0)
					ST7735_OutChar(map[y][x]+'0');
				else
					ST7735_OutChar(' ');
			}
			ST7735_OutChar('\n');
		}
	}
}


