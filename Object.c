#include <stdint.h>
#include "Object.h"

#include "ST7735.h"
#include "Graphics2D.h"
#include "Map.h"
#include "ADC.h"
#include "Player.h"
#include "Rock.h"
#include "Spike.h"
#include "Horf.h"
#include "AttackFly.h"

#define SIZE 50

Object objects[SIZE];
uint8_t playerIndex;
uint8_t objectIndex;

void RunInit(void) {
	Map_Init(ADC_In());
	PlayerCreate(RequestObject(1));
	UpdateHeart(6,6);
}

void RunLogic(uint64_t delta) {
	for(uint8_t x = 0; x < SIZE; x++) {
		if(objects[x].logic != 0)
			(objects[x].logic)(&objects[x], &objects[playerIndex], delta); 
		objects[x].hasCollided = 0;
		if(objects[x].x < 0 || objects[x].y < 0 || objects[x].x/100 + objects[x].width > ROOM_WIDTH || objects[x].y/100 + objects[x].height > ROOM_HEIGHT) {
			objects[x].hasCollided = 1;
			objects[x].collidedWith = &objects[x];
			ObjectRevert(&objects[x]);
		}
	}
	for(uint8_t x = 0; x < objectIndex; x++) {
		for(uint8_t y = 0; y < objectIndex; y++) {
			if(y != x) {
				if (objects[x].x < objects[y].x+objects[y].width*100 && objects[x].x+objects[x].width*100 > objects[y].x  
			  &&  objects[x].y < objects[y].y+objects[y].height*100 && objects[x].y+objects[x].height*100 > objects[y].y ) {
					objects[x].hasCollided = 1;
					objects[y].hasCollided = 1;
					objects[x].collidedWith = &objects[y];
					objects[y].collidedWith = &objects[x];
					if(!(objects[x].isPassable | objects[y].isPassable)) {
						ObjectRevert(&objects[x]);
						ObjectRevert(&objects[y]);
					}
				}
			}
		}
	}
	if(objects[playerIndex].variables[7]) {
		UpdateHeart(objects[playerIndex].variables[2],objects[playerIndex].variables[1]);
		objects[playerIndex].variables[7] = 0;
	}
}

uint8_t RunRender(void) {
	CheckUpdates();
	ClearBuffer();
	if(objects[playerIndex].isRendered) {
		for(uint8_t x = 0; x < objectIndex; x++) {
			if(objects[x].isRendered)
				DrawImage(objects[x].x/100, objects[x].y/100, objects[x].image, objects[x].width, objects[x].height);
			else {
				for(int y = x+1; y < objectIndex; y++) {
					objects[y-1] = objects[y];
				}
				x--;
				objectIndex--;
			}
		}
		DrawBuffer();
		return 1;
	}
	else {
		ST7735_FillRect(0,0,160,128,0);
		DrawString(0,0,"GAME OVER",0xFFFF);
		return 0;
	}
}

Object* RequestObject(uint8_t isPlayer) {
	if(isPlayer) playerIndex = objectIndex;
	return &objects[objectIndex++];
}

void ObjectLogic(Object *this, Object *player, uint64_t delta) {
	(*this).lastx = (*this).x;
	(*this).lasty = (*this).y;
}

void ObjectRevert(Object *this) {
	(*this).x = (*this).lastx;
	(*this).y = (*this).lasty;
}
