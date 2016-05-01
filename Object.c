#include <stdint.h>
#include "Object.h"

#include "Graphics2D.h"

#define SIZE 50

Object objects[SIZE];
uint8_t playerIndex;
uint8_t objectIndex;

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
}

void RunRender(void) {
	if(objects[playerIndex].variables[7]) {
		UpdateHeart(objects[playerIndex].variables[2],objects[playerIndex].variables[1]);
		objects[playerIndex].variables[7] = 0;
	}
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
