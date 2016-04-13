#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics.h"

int main(void) {
	int height = 160;
	int width = 128;
	Vector3 cube[8] = {{{-1,2,1}},{{1,2,1}},{{-1,-1,1}},{{1,-1,1}},{{-1,2,-1}},{{1,2,-1}},{{1,-1,-1}},{{-1,-1,-1}}};
	Vector3 faces[12] = {{{0,1,2}},{{1,2,3}},{{1,3,6}},{{1,5,6}},{{0,1,4}},{{1,4,5}},{{2,3,7}},{{3,6,7}},{{0,2,7}},{{0,4,7}},{{4,5,6}},{{4,6,7}}};
	for(int x = 0; x < 8; x++) {
		cube[x] = transform(cube[x],scale((Vector3){{20,20,20}}));
	}
	
	Matrix4 rotX = rotate(0,0);
	Matrix4 rotY = rotate(5,1);
	Matrix4 rotZ = rotate(0,2);
	

	Vector3 eye = {{100,50,100}};
	Vector3 target = {{0,0,0}};
	Vector3 up = {{0,1,0}};
	Matrix4 camera = lookAt(eye,target,up);
	Matrix4 proj = pers(width,height,100,10);
	Matrix4 mvp = multiply(camera,proj);
	TExaS_Init();         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB);
	while(1) {
		for(int x = 0; x < 8; x++) {
			cube[x] = transform(cube[x],rotX);
			cube[x] = transform(cube[x],rotY);
			cube[x] = transform(cube[x],rotZ);
		}
		
		for(int x = 0; x < 12; x++) {			
			Vector2 point1 = project(cube[(int)faces[x].V[0]],mvp,width,height);
			Vector2 point2 = project(cube[(int)faces[x].V[1]],mvp,width,height);
			Vector2 point3 = project(cube[(int)faces[x].V[2]],mvp,width,height);
			drawLine(point1,point2,ST7735_YELLOW);
			drawLine(point2,point3,ST7735_YELLOW);
			drawLine(point3,point1,ST7735_YELLOW);

		}
		Output_Clear();
	}
}
