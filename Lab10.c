#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics2D.h"
#include <math.h>
#define PI 3.141592654



int main(void) {
  TExaS_Init();
  Graphics2DInit();
  while(1) {
		Render();
	}
}
