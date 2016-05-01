// Sound.c
#include <stdint.h>
#include "Sound.h"
#include "DAC.h"
#include "SysTickInts.h"
#include "texas.h"

uint32_t period = 7256;

Sound bgm;
Sound cur;
uint8_t cvalues[2049];
uint8_t bvalues[2049];

uint8_t GetValue(Sound c) {
	if(c.vi-(int32_t)c.off < 0) {
		return c.values[2049+c.vi-c.off];
	}
	return c.values[c.vi-c.off];
}
void Sound_Init(void){
	DAC_Init();  
	SysTick_Init(period);
	cur.values = cvalues;
	bgm.values = bvalues;
};

void Sound_BGM_Play(const uint8_t *pt, uint32_t count){
	bgm.sound = pt;
	bgm.size = count;
	bgm.loop = 1;
	bgm.p = 0;
	bgm.off = 0;
	bgm.len = 0;
};

void Sound_Play(const uint8_t *pt, uint32_t count, uint8_t lp){
	cur.sound = pt;
	cur.size = count;
	cur.loop = lp;
	cur.p = 0;
	cur.off = 0;
	cur.len = 0;
};
// Plays current sample(s), sounds are played by ducking the BGM. Need to actually implement volume
void SysTick_Handler(void){	
	uint8_t out = 0;
	out |= Decode(&bgm);
	uint8_t snd = Decode(&cur);
	if(snd != 0) {
		out *= (out-snd)/out;
		out = snd;
	}
	DAC_Out(out);
}

// Method that reads a sound struct and decodes it, sound is stored in a byte based LZ77 compression.
uint8_t Decode(Sound *cc) {
	if((*cc).size == 0) return 0;
	uint8_t out = 0;
	if((*cc).off == 0 && ((*cc).sound[(*cc).p] & 0x80) == 0x80) {
		(*cc).off = ((((*cc).sound[(*cc).p] & ~0x80) << 4) | ((*cc).sound[(*cc).p+1] >> 4))+1;
		(*cc).len = ((*cc).sound[(*cc).p+1] & 0xF)+4;
		(*cc).cnt = 0;
		(*cc).p+=2;
	}
	
	if((*cc).off == 0) {
		out = (*cc).sound[(*cc).p] & 0x7F;
		(*cc).values[(*cc).vi] = (*cc).sound[(*cc).p]; 
		(*cc).p++;
	}
	else if((*cc).off > 0) {
		(*cc).values[(*cc).vi] = GetValue((*cc));
		out = (*cc).values[(*cc).vi] & 0x7F;
		(*cc).cnt++;
		if((*cc).cnt >= (*cc).len) {
			(*cc).off = 0;
		}
	}
	
	if((*cc).loop == 1) (*cc).p %= (*cc).size;
	
	if((*cc).p >= (*cc).size) {
		(*cc).p = (*cc).size;
		out = 0;
	}
	else {
		(*cc).vi = ((*cc).vi+1)%2049;
	}
	return out;
}

uint8_t Sound_Ready(void) {
	return 0;
}
