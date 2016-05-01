#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "Bullet.h"

#include "Object.h"
#include "Player.h"
#include "Graphics2D.h"

#define BULLET_SIZE 4
#define ENEMY_SIZE 1

#define velocityx variables[0]
#define velocityy variables[1]
#define range variables[2]
#define damage variables[3]
#define origin variables[4]

void(*enemies[ENEMY_SIZE])(Object *this, Object player, uint64_t delta) = {0};

const unsigned short bullet[] = {
 0xFFFF, 0xBC8E, 0xBC8E, 0xFFFF, 0xBC8E, 0xFFFA, 0xF779, 0xBC8E, 0xBC8E, 0xF779, 0xF779, 0xBC8E, 0xFFFF, 0xBC8E, 0xBC8E, 0xFFFF,
};

void BulletCreate(Object *this, uint16_t x, uint16_t y, int16_t vx, int16_t vy, uint16_t rng, uint16_t dmg, uint32_t originator) {
	(*this).image = bullet;
	(*this).width = BULLET_SIZE;
	(*this).height = BULLET_SIZE;
	(*this).x = x;
	(*this).y = y;
	(*this).hasCollided = 0;
	(*this).isPassable = 1;
	(*this).isRendered = 1;
	(*this).logic = BulletLogic;		
	(*this).velocityx = vx;
	(*this).velocityy = vy;
	(*this).range = rng;
	(*this).damage = dmg;
	(*this).origin = originator;
}

void BulletLogic(Object *this, Object *player, uint64_t delta) {
	ObjectLogic(this,player,delta);
	if((*this).isRendered == 0) return;
	int32_t dx = (int64_t)delta * (*this).velocityx / 100;
	int32_t dy = (int64_t)delta * (*this).velocityy / 100;
	(*this).x += dx;
	(*this).y += dy;
	(*this).range -= sqrt(dx*dx+dy*dy);
	if((*this).range <= 0) {
		(*this).isRendered = 0;
		return;
	}
	if((*this).hasCollided) {
		if((void*)(*(*this).collidedWith).logic != (void*)(*this).origin) {
			(*this).isRendered = 0;
		}
		if((*(*this).collidedWith).logic == PlayerLogic && (*(Object*)(*this).origin).logic != PlayerLogic) {
			(*player).variables[1] -= (*this).damage;
			if((*player).variables[1] < 0) (*player).variables[1] = 0;
			(*player).variables[7] = 1;
		}
		else if(this == (*this).collidedWith) {
			return;
		}
		else {
			for(int x = 0; x < ENEMY_SIZE; x++) {
				if((*(*this).collidedWith).logic == enemies[x]) {
					(*(*this).collidedWith).variables[0] -= (*this).damage;
				}
			}
		}
	}
}
