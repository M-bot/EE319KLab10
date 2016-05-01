#include <stdint.h>
#include "GameTick.h"

#include "Timer0.h"

uint64_t systemTime;
uint64_t lastTime;

void GameTickInit(void) {
	Timer0_Init(GameTickHandler,8000);
}

void GameTickHandler(void) {
	systemTime++;
}

uint64_t GameTickDelta(void) {
	return systemTime - lastTime;
}	

void GameTickRecord(void) {
	lastTime = systemTime;
}
