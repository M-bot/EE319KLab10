#include <stdint.h>
#include "Spike.h"

#include "Object.h"
#include "Player.h"
#include "Graphics2D.h"
#include "5Pos_Switch.h"

#define SPIKE_WIDTH 5
#define SPIKE_HEIGHT 10

#define damage variables[0]

const unsigned short spike[] = {
 0xFFFF, 0x6B6F, 0x630D, 0x7BF0, 0xFFFF, 0x0842, 0x31A8, 0x4208, 0x31A7, 0x18C4, 0x6B4D, 0x528B, 0x8411, 0x738E, 0x4A6A, 0xFFFF,
 0x4229, 0x94B3, 0x5AEC, 0xFFFF, 0xFFFF, 0x4209, 0x73AF, 0x4229, 0xFFFF, 0xFFFF, 0x4A49, 0x738E, 0x39E8, 0xFFFF, 0xFFFF, 0x5ACB,
 0x632D, 0x52AB, 0xFFFF, 0xFFFF, 0x73AF, 0x5AEC, 0x630D, 0xFFFF, 0xFFFF, 0x9CD3, 0x0842, 0x5AEC, 0xFFFF, 0xFFFF, 0xFFFF, 0x5AEC,
 0xFFFF, 0xFFFF,

};


void SpikeCreate(Object *this, uint8_t x, uint8_t y, uint8_t dmg) {
	Switch_Init();
	(*this).image = spike;
	(*this).width = SPIKE_WIDTH;
	(*this).height = SPIKE_HEIGHT;
	(*this).x = x*100;
	(*this).y = y*100;
	(*this).hasCollided = 0;
	(*this).isPassable = 0;
	(*this).isRendered = 1;
	(*this).logic = SpikeLogic;
	(*this).damage = dmg;
}

uint16_t scooldown;
void SpikeLogic(Object *this, Object *player, uint64_t delta) {
	ObjectLogic(this,player,delta);
	if((*this).hasCollided) {
		if((*(*this).collidedWith).logic == PlayerLogic && scooldown == 0) {
			scooldown = 50;
			(*player).variables[1] -= (*this).damage;
			if((*player).variables[1] < 0) (*player).variables[1] = 0;
			(*player).variables[7] = 1;
		}
		if(scooldown != 0) {
			scooldown--;
		}
	}
}
