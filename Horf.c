#include <stdint.h>
#include <math.h>
#include "Horf.h"

#include "Object.h"
#include "Bullet.h"
#include "Graphics2D.h"
#include "5Pos_Switch.h"

#define HORF_WIDTH 11
#define HORF_HEIGHT 10

#define currentHealth variables[0]
#define bulletVelocity variables[1]
#define bulletRange variables[2]
#define bulletDamage variables[3]
#define bulletCooldown variables[4]
const unsigned short horf[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0010, 0xC63C,
 0xC63C, 0xC63C, 0x0010, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0016, 0x0016, 0x0000, 0xA534, 0x0000, 0x9CF9, 0x0016, 0x0000,
 0xFFFF, 0x0000, 0x0010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7397, 0x0000, 0x0000, 0x0010, 0x000A, 0x000A,
 0xC63C, 0x0000, 0x9CF9, 0x000A, 0x000A, 0x0010, 0x0000, 0x0000, 0xC63C, 0x0000, 0x0000, 0xC63C, 0xC63C, 0x0016, 0x0000, 0x0000,
 0xC63C, 0x0000, 0x0000, 0x9CF9, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0x9CF9, 0x0000, 0xFFFF, 0x0000, 0xC63C,
 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x9CF9, 0xC63C, 0xC63C, 0xC63C, 0x9CF9,
 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,

};


void HorfCreate(Object *this, uint8_t x, uint8_t y) {
	Switch_Init();
	(*this).image = horf;
	(*this).width = HORF_WIDTH;
	(*this).height = HORF_HEIGHT;
	(*this).x = x*100;
	(*this).y = y*100;
	(*this).hasCollided = 0;
	(*this).isPassable = 0;
	(*this).isRendered = 1;
	(*this).logic = HorfLogic;
	(*this).currentHealth = 6;		
	(*this).bulletVelocity = 18;
	(*this).bulletRange = 3000;
	(*this).bulletDamage = 1;
	(*this).bulletCooldown = 25;
}

uint16_t hcooldown;
void HorfLogic(Object *this, Object *player, uint64_t delta) {
	ObjectLogic(this,player,delta);
	if((*this).currentHealth  <= 0) {
		(*this).isRendered = 0;
		return;
	}
	int16_t centerx = (*this).x + (*this).width * 50;
	int16_t centery = (*this).y + (*this).height * 50;
	int32_t vx = (-(*this).x+(*player).x);
	int32_t vy = (-(*this).y+(*player).y);
	int32_t c = sqrt(vx*vx+vy*vy);
	vx *= (*this).bulletVelocity;
	vy *= (*this).bulletVelocity;
	vx /= c;
	vy /= c;
	if(hcooldown == 0) {
		hcooldown = (*this).bulletCooldown ;
		if(c < 2500) BulletCreate(RequestObject(0),centerx,centery,vx,vy,(*this).bulletRange,(*this).bulletDamage,(uint32_t)HorfLogic);
	}
	else {
		hcooldown--;
	}
}
