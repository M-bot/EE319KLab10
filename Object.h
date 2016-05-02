#ifndef OBJECT_H
#define OBJECT_H
#include <stdint.h>

typedef struct Object Object;
struct Object {
	const uint16_t * image;
	int32_t x;
	int32_t y;
	int32_t lastx;
	int32_t lasty;
	uint8_t width;
	uint8_t height;
	uint8_t hasCollided;
	uint8_t isPassable;
	Object *collidedWith;
	uint8_t isRendered;
	void(*logic)(Object *this, Object *player, uint64_t delta);
	int32_t variables[10];
};

void RunInit(void);
void RunLogic(uint64_t delta);
uint8_t RunRender(void);
Object* RequestObject(uint8_t isPlayer);
void ObjectLogic(Object *this, Object *player, uint64_t delta);
void ObjectRevert(Object *this);
#endif
