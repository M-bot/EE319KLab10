#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "Bullet.h"

#include "Object.h"
#include "Player.h"
#include "Horf.h"
#include "AttackFly.h"
#include "Graphics2D.h"

#define BULLET_SIZE 4
#define ENEMY_SIZE 2

#define velocityx variables[0]
#define velocityy variables[1]
#define range variables[2]
#define damage variables[3]
#define origin variables[4]

void(*const enemies[ENEMY_SIZE])(Object *this, Object *player, uint64_t delta) = {HorfLogic, AttackFlyLogic};

const unsigned short bullet[] = {
 0xFFFF, 0xBC8E, 0xBC8E, 0xFFFF, 0xBC8E, 0xFFFA, 0xF779, 0xBC8E, 0xBC8E, 0xF779, 0xF779, 0xBC8E, 0xFFFF, 0xBC8E, 0xBC8E, 0xFFFF,
};

const unsigned short bulletred[] = {
 0xFFFF, 0x1074, 0x1074, 0xFFFF, 0x1074, 0xA4DF, 0x83BF, 0x1074, 0x1074, 0x83BF, 0x83BF, 0x1074, 0xFFFF, 0x1074, 0x1074, 0xFFFF,
};

void BulletCreate(Object *this, uint16_t x, uint16_t y, int16_t vx, int16_t vy, uint16_t rng, uint16_t dmg, uint32_t originator) {
	(*this).image = originator == (uint32_t)PlayerLogic ? bullet : bulletred;
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
	if((*this).hasCollided && (*(*this).collidedWith).logic != BulletLogic) {
		if((void*)(*(*this).collidedWith).logic != (void*)(*this).origin) {
			(*this).isRendered = 0;
		}
		if((*(*this).collidedWith).logic == PlayerLogic && (*this).origin != (uint32_t)PlayerLogic) {
			(*player).variables[1] -= (*this).damage;
			if((*player).variables[1] < 0) (*player).variables[1] = 0;
			(*player).variables[7] = 1;
		}
		else if(this == (*this).collidedWith) {
			return;
		}
		else {
			for(int x = 0; x < ENEMY_SIZE; x++) {
				if((*(*this).collidedWith).logic == enemies[x] && (*this).origin == (uint32_t)PlayerLogic) {
					(*(*this).collidedWith).variables[0] -= (*this).damage;
				}
			}
		}
	}
}
