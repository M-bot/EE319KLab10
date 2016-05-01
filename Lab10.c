#include <stdint.h>

#include "TExaS.h"
#include "Graphics2D.h"
#include "GameTick.h"
#include "Object.h"
#include "Player.h"
#include "Rock.h"
#include "Spike.h"
#include "Horf.h"

int main(void){
  TExaS_Init();         // Bus clock is 80 MHz 
	Graphics2DInit();
	GameTickInit();
	PlayerCreate(RequestObject(1));
	RockCreate(RequestObject(0), 10, 10);
	SpikeCreate(RequestObject(0), 25, 25, 1);
	HorfCreate(RequestObject(0), 10, 25);
	UpdateHeart(6,6);
	GameTickRecord();
	while(1) {
		RunLogic(GameTickDelta());
		GameTickRecord();
		RunRender();
		Render();
	}
}
