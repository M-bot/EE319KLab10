#include <stdint.h>
#include <math.h>
#include "Player.h"

#include "Object.h"
#include "Bullet.h"
#include "Graphics2D.h"
#include "5Pos_Switch.h"

#define FIRE_WIDTH 11
#define FIRE_HEIGHT 14

#define velocity variables[0]
#define currentHealth variables[1]
#define maxHealth variables[2]
#define bulletVelocity variables[3]
#define bulletRange variables[4]
#define bulletDamage variables[5]
#define bulletCooldown variables[6]
#define updateHeart variables[7]

const unsigned short player[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xC63C,
 0x0000, 0xC63C, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x9CF9, 0xC63C, 0xC63C, 0xC63C, 0x9CF9, 0x0000, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x9CF9, 0xC63C, 0x0000, 0xC63C, 0x9CF9, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x9CAC,
 0x0000, 0x0000, 0x0000, 0x9CAC, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x9CAC, 0xCE53, 0x9CF9, 0x9CF9, 0x9CF9, 0xCE53, 0x9CAC,
 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xCE53, 0xCE53, 0x0000, 0xFFFF, 0x0000, 0xCE53, 0xCE53, 0x0000, 0xFFFF, 0x0000, 0x7397, 0xCE53,
 0xCE53, 0x0000, 0x0000, 0x0000, 0xCE53, 0xCE53, 0x7397, 0x0000, 0x0000, 0x9CF9, 0x0000, 0x0000, 0xC63C, 0x0000, 0x9CF9, 0x0000,
 0x0000, 0x9CF9, 0x0000, 0x0000, 0x9CF9, 0xFFFF, 0x0000, 0xC63C, 0xC63C, 0xC63C, 0xFFFF, 0x0000, 0x9CF9, 0x0000, 0x0000, 0x9CF9,
 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0x9CF9, 0x0000, 0xFFFF, 0x0000, 0xC63C, 0xC63C, 0xC63C, 0xC63C, 0xC63C,
 0xC63C, 0xC63C, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x9CF9, 0xC63C, 0xC63C, 0xC63C, 0x9CF9, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF,

};



uint16_t cooldown;
void PlayerCreate(Object *this) {
	Switch_Init();
	(*this).image = player;
	(*this).width = PLAYER_WIDTH;
	(*this).height = PLAYER_HEIGHT;
	(*this).x = (ROOM_WIDTH/2 - PLAYER_WIDTH/2)*100;
	(*this).y = (ROOM_HEIGHT/2 - PLAYER_HEIGHT/2)*100;
	(*this).hasCollided = 0;
	(*this).isPassable = 0;
	(*this).isRendered = 1;
	(*this).logic = PlayerLogic;
	(*this).velocity = 22;	
	(*this).currentHealth = 6;		
	(*this).maxHealth = 6;
	(*this).bulletVelocity = 30;
	(*this).bulletRange = 3000;
	(*this).bulletDamage = 1;
	(*this).bulletCooldown = 25;
	(*this).updateHeart = 0;
}

void PlayerLogic(Object *this, Object *player, uint64_t delta) {
	ObjectLogic(this,player,delta);
	if((*this).isRendered == 0) return;
	if((*this).currentHealth  <= 0) {
		(*this).isRendered = 0;
		return;
	}
	int8_t mov[2];
	Mov_In(mov);
	(*this).x += mov[0] * (int64_t)delta * (*this).velocity / 100;
	(*this).y += mov[1] * (int64_t)delta * (*this).velocity / 100;
	int8_t fire[2];
	Fire_In(fire);
	int16_t centerx = (*this).x + (*this).width * 50;
	int16_t centery = (*this).y + (*this).height * 50;
	if((fire[0] != 0 || fire[1] != 0) && cooldown == 0) {	
		int32_t vx = fire[0];
		int32_t vy = fire[1];
		int32_t c = sqrt(vx*vx+vy*vy);
		vx *= (*this).velocity;
		vy *= (*this).velocity;
		vx /= c;
		vy /= c;
		cooldown = (*this).bulletCooldown ;
		BulletCreate(RequestObject(0),centerx+(FIRE_WIDTH*50*fire[0]),centery+(FIRE_HEIGHT*50*fire[1])
			,fire[0]*(*this).bulletVelocity,fire[1]*(*this).bulletVelocity,(*this).bulletRange,(*this).bulletDamage,(uint32_t)PlayerLogic);
	}
	
	if(cooldown != 0) {
		cooldown--;
	}
}
