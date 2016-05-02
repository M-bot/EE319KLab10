#include <stdint.h>
#include "Room.h"

#include "Object.h"

#define SIZE 3

uint8_t room0clear ;

void Room0Create(void) {
	room0clear = 1;
}


uint8_t room1clear;
uint8_t room1counter;

void Room1Removal(void) {
	if(--room1counter <= 0) {
		room1clear = 1;
	}
}

void Room1Create(void) {
	room1counter = 1;
	if(room1clear) {
		Object * cur = RequestObject(0);
		RockCreate(cur,50,10);
	} else {
		Object * cur = RequestObject(0);
		RockCreate(cur,50,10);
		cur = RequestObject(0);
		AttackFlyCreate(cur,10,10);
		cur->onremove = Room1Removal;
	}
}

uint8_t room2clear;
uint8_t room2counter;

void Room2Removal(void) {
	if(--room2counter <= 0) {
		room2clear = 1;
	}
}

void Room2Create(void) {
	room2counter = 2;
	if(room2clear) {
		
	} else {
		Object * cur = RequestObject(0);
		AttackFlyCreate(cur,10,10);
		cur->onremove = Room2Removal;
		cur = RequestObject(0);
		AttackFlyCreate(cur,110,10);
		cur->onremove = Room2Removal;		
		RockCreate(cur,50,10);
		cur = RequestObject(0);
		cur = RequestObject(0);
		HorfCreate(cur,110,60);
		cur->onremove = Room2Removal;
	}
}



uint8_t * clears[SIZE] = {&room0clear,&room1clear,&room2clear};
void(*const creates[SIZE])(void) = {Room0Create,Room1Create,Room2Create};

void RoomCreate(Room * room, uint8_t num) {
	(*room).cleared = clears[num-1];
	(*room).create = creates[num-1];
}
