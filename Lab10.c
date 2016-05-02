#include <stdint.h>

#include "TExaS.h"
#include "Graphics2D.h"
#include "GameTick.h"
#include "Object.h"

int main(void){
  TExaS_Init();         // Bus clock is 80 MHz 
	Graphics2DInit();
	GameTickInit();
  RunInit();
	GameTickRecord();
	do {
		Render();
		RunLogic(GameTickDelta());
		GameTickRecord();
		
	} while(RunRender());
}
