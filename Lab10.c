#include "Matrix.h"
#include "ST7735.h"
#include "TExaS.h"
#include "print.h"
#include "tm4c123gh6pm.h"
#include "Graphics.h"
#include <math.h>
#define PI 3.141592654



int main(void) {
	int height = 86;
	int width = 160;
	Vector3 cube[8] = {{{-1,1,1}},{{1,1,1}},{{-1,-1,1}},{{1,-1,1}},{{-1,1,-1}},{{1,1,-1}},{{-1,-1,-1}},{{1,-1,-1}}};
	Vector3 faces[12] = {{{0,2,1}},{{1,2,3}},{{1,3,7}},{{1,7,5}},{{0,1,4}},{{1,5,4}},{{2,6,3}},{{3,6,7}},{{6,2,0}},{{0,4,6}},{{4,5,7}},{{4,7,6}}};
	for(int x = 0; x < 8; x++) {
		cube[x] = transform(cube[x],scale((Vector3){{20,20,20}}));
	}
	
	Matrix4 rotX = rotate(0,0);
	Matrix4 rotY = rotate(0,1);
	Matrix4 rotZ = rotate(0,2);
	

	Vector3 cameraPos = {{100,0,100}};	
	int pitch = 0, yaw = 45;
	Vector3 up = {{0,1,0}};
	Matrix4 proj = pers(90,90,1,1);
	
	TExaS_Init();         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB);
	ST7735_SetRotation(1);
	ST7735_FillRect(0, 86, 160, 42, ST7735_WHITE);
	
	while(1) {
		Vector3 cameraFront = {{cos(pitch*PI/180)*cos(yaw*PI/180),sin(pitch*PI/180),cos(pitch*PI/180)*sin(yaw*PI/180)}};
		cameraFront = normal(cameraFront);
		Matrix4 camera = lookAt(cameraPos,subtract(cameraPos,cameraFront),up);
	
		for(int x = 0; x < 8; x++) {
			cube[x] = transform(cube[x],rotX);
			cube[x] = transform(cube[x],rotY);
			cube[x] = transform(cube[x],rotZ);
		}

		for(int x = 0; x < 12; x++) {			
			Vector3 norma = cross(subtract(cube[(int)faces[x].V[1]],cube[(int)faces[x].V[0]]),subtract(cube[(int)faces[x].V[2]],cube[(int)faces[x].V[0]]));
			norma = transform(norma,camera);
			if(norma.vZ < 0) continue;
			Vector2 point1,point2,point3;
			uint32_t failure = 0;
			failure |= project(&point1,transform(cube[(int)faces[x].V[0]],camera),proj,width,height);
			failure |= project(&point2,transform(cube[(int)faces[x].V[1]],camera),proj,width,height);
			failure |= project(&point3,transform(cube[(int)faces[x].V[2]],camera),proj,width,height);
			if(!failure)
				drawTriangle(point1,point2,point3,x % 3 == 0 ? ST7735_BLUE : x % 3 == 1 ? ST7735_GREEN : ST7735_RED);
		}
		yaw=(yaw+10)%360;
		sendScreen();
	}
}
