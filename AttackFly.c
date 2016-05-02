#include <stdint.h>
#include <math.h>
#include "AttackFly.h"

#include "Object.h"
#include "Player.h"
#include "Bullet.h"
#include "Graphics2D.h"
#include "5Pos_Switch.h"

#define ATTACKFLY_WIDTH 10
#define ATTACKFLY_HEIGHT 5

#define currentHealth variables[0]
#define velocity  variables[1]
#define damage  variables[2]
#define cooldown variables[3]

const unsigned short attackfly[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0009, 0x10AD, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x4A69, 0x0000, 0x08B4, 0x219F, 0x001D,
 0x0007, 0x0000, 0x4A49, 0xFFFF, 0x2946, 0xFFFF, 0xFFFF, 0x2A56, 0x5C1F, 0x001A, 0x39AF, 0xFFFF, 0xFFFF, 0x2946, 0x0841, 0xFFFF,
 0xFFFF, 0x10E7, 0x29B2, 0x0009, 0x52AB, 0xFFFF, 0xFFFF, 0x0841, 0xFFFF, 0x0000, 0x2105, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
 0x0001, 0xFFFF,

};



void AttackFlyCreate(Object *this, uint8_t x, uint8_t y) {
	Switch_Init();
	(*this).image = attackfly;
	(*this).width = ATTACKFLY_WIDTH;
	(*this).height = ATTACKFLY_HEIGHT;
	(*this).x = x*100;
	(*this).y = y*100;
	(*this).hasCollided = 0;
	(*this).isPassable = 1;
	(*this).isRendered = 1;
	(*this).logic = AttackFlyLogic;
	(*this).currentHealth = 6;		
	(*this).velocity = 10;
	(*this).damage = 1;
	(*this).cooldown = 50;
}

uint16_t acooldown;
void AttackFlyLogic(Object *this, Object *player, uint64_t delta) {
if((*this).currentHealth  <= 0) {
		(*this).isRendered = 0;
		return;
	}
	ObjectLogic(this,player,delta);
	int32_t vx = (-(*this).x+(*player).x);
	int32_t vy = (-(*this).y+(*player).y);
	int32_t c = sqrt(vx*vx+vy*vy);
	vx *= (*this).velocity;
	vy *= (*this).velocity;
	vx /= c;
	vy /= c;
	(*this).x += (int64_t)delta * vx / 100;
	(*this).y += (int64_t)delta * vy / 100;
	
	if((*this).hasCollided) {
		if((*(*this).collidedWith).logic == PlayerLogic && acooldown == 0) {
			acooldown = (*this).cooldown;
			(*player).variables[1] -= (*this).damage;
			if((*player).variables[1] < 0) (*player).variables[1] = 0;
			(*player).variables[7] = 1;
		}
		if(acooldown != 0) {
			acooldown--;
		}
	}
}
