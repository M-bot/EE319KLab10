#include <stdint.h>
#include "Object.h"

#include "ST7735.h"
#include "Graphics2D.h"
#include "Map.h"
#include "ADC.h"
#include "Room.h"

#define SIZE 50

Object objects[SIZE];
uint8_t playerIndex;
uint8_t objectIndex;
Room currentRoom;
int8_t currentX = MAP_DATA_SIZE/2;
int8_t currentY = MAP_DATA_SIZE/2;

const int8_t doordir[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
const uint32_t playerdoor[4][2] = {{ROOM_WIDTH/2 - PLAYER_WIDTH/2,ROOM_HEIGHT-PLAYER_HEIGHT-5},{5,ROOM_HEIGHT/2 - PLAYER_HEIGHT/2},{ROOM_WIDTH/2 - PLAYER_WIDTH/2,5},{ROOM_WIDTH-PLAYER_WIDTH-5,ROOM_HEIGHT/2 - PLAYER_HEIGHT/2}};

const unsigned short dr[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

void DoorLogic(Object *this, Object *player, uint64_t delta) {
	ObjectLogic(this,player,delta);
	if((*this).hasCollided) {
		if(*currentRoom.cleared != 1) return;
		if(Get_Room_Data(currentX+doordir[this->variables[0]][0],currentY+doordir[this->variables[0]][1]) != 0) {
			Set_Room(currentX,currentY,1);
			Set_Room(currentX,currentY,2);
			currentX += doordir[this->variables[0]][0];
			currentY += doordir[this->variables[0]][1];
			Set_Room(currentX,currentY,0);
			DrawMap();
			objectIndex = 5;
			RoomCreate(&currentRoom,Get_Room_Data(currentX,currentY));
			*currentRoom.cleared = (Get_Map_Data(currentX,currentY) & 0x2) >> 1;
			currentRoom.create();
			objects[playerIndex].x = playerdoor[this->variables[0]][0]*100;
			objects[playerIndex].y = playerdoor[this->variables[0]][1]*100;
		}
	}
}

void RunInit(void) {
	Map_Init(ADC_In());
	PlayerCreate(RequestObject(1));
	objects[objectIndex].logic = DoorLogic;
	objects[objectIndex].image = dr;
	objects[objectIndex].x = (ROOM_WIDTH/2-5)*100;
	objects[objectIndex].y = 1;
	objects[objectIndex].width = 10;
	objects[objectIndex].height = 2;
	objects[objectIndex].isRendered = 1;
	objects[objectIndex].isPassable = 1;
	objects[objectIndex++].variables[0] = 0;
	objects[objectIndex].logic = DoorLogic;
	objects[objectIndex].image = dr;
	objects[objectIndex].x = (ROOM_WIDTH/2-5)*100;
	objects[objectIndex].y = (ROOM_HEIGHT-2)*100;
	objects[objectIndex].width = 10;
	objects[objectIndex].height = 2;
	objects[objectIndex].isRendered = 1;
	objects[objectIndex].isPassable = 1;
	objects[objectIndex++].variables[0] = 2;
	objects[objectIndex].logic = DoorLogic;
	objects[objectIndex].image = dr;
	objects[objectIndex].x = 0;
	objects[objectIndex].y = (ROOM_HEIGHT/2-5)*100;
	objects[objectIndex].width = 2;
	objects[objectIndex].height = 10;
	objects[objectIndex].isRendered = 1;
	objects[objectIndex].isPassable = 1;
	objects[objectIndex++].variables[0] = 3;
	objects[objectIndex].logic = DoorLogic;
	objects[objectIndex].image = dr;
	objects[objectIndex].x = (ROOM_WIDTH-2)*100;
	objects[objectIndex].y = (ROOM_HEIGHT/2-5)*100;
	objects[objectIndex].width = 2;
	objects[objectIndex].height = 10;
	objects[objectIndex].isRendered = 1;
	objects[objectIndex].isPassable = 1;
	objects[objectIndex++].variables[0] = 1;
	DrawHearts(objects[playerIndex].variables[1],objects[playerIndex].variables[2]);
	RoomCreate(&currentRoom,1);
	currentRoom.create();
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
					if(objects[x].collidedWith->logic != PlayerLogic || objects[y].collidedWith->logic != PlayerLogic) {
						objects[x].collidedWith = &objects[y];
						objects[y].collidedWith = &objects[x];
					}
					if(!(objects[x].isPassable | objects[y].isPassable)) {
						ObjectRevert(&objects[x]);
						ObjectRevert(&objects[y]);
					}
				}
			}
		}
	}

}

uint8_t RunRender(void) {
	ClearBuffer();	
	if(objects[playerIndex].variables[7]) {
		DrawHearts(objects[playerIndex].variables[1],objects[playerIndex].variables[2]);
		objects[playerIndex].variables[7] = 0;
	}
	if(objects[playerIndex].isRendered) {
		for(uint8_t x = 0; x < objectIndex; x++) {
			if(objects[x].isRendered)
				DrawImage(objects[x].x/100, objects[x].y/100, objects[x].image, objects[x].width, objects[x].height);
			else {
				for(int y = x+1; y < objectIndex; y++) {
					objects[y-1] = objects[y];
				}
				if(objects[x].onremove != 0) objects[x].onremove();
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
