#include "Matrix.h"
#include "Graphics.h"
#include "ST7735.h"
#include <math.h>
#define PI 3.141592654
#define WIDTH 160
#define HEIGHT 86

uint16_t screen[HEIGHT*WIDTH];

void sendScreen(void) {
	ST7735_DrawBitmap(0,HEIGHT,screen,WIDTH,HEIGHT);
	for(int x = 0; x < HEIGHT*WIDTH; x++)
		screen[x] = 0;
}

Matrix4 ortho(float width, float height, float zfar, float znear) {
	return (Matrix4){{{1/width,0,0,0},{0,1/height,0,0},{0,0,-2/(zfar-znear),0},{0,0,-(zfar+znear)/(zfar-znear),1}}};
}

Matrix4 pers(float fovx, float fovy, float zfar, float znear) {
	return (Matrix4){{{atan(fovx/2),0,0,0},{0,atan(fovy/2),0,0},{0,0,-(zfar+znear)/(zfar-znear),-1},{0,0,-2*(zfar*znear)/(zfar-znear),0}}};
}

Matrix4 rotate(float degrees, int axis) {
	float rads = degrees*PI/180;
	if(axis == 0) 
		return (Matrix4){{{1,0,0,0},{0,cos(rads),-sin(rads),0},{0,sin(rads),cos(rads),0},{0,0,0,1}}};
	if(axis == 1) 
		return (Matrix4){{{cos(rads),0,sin(rads),0},{0,1,0,0},{-sin(rads),0,cos(rads),0},{0,0,0,1}}};
	return (Matrix4){{{cos(rads),-sin(rads),0,0},{sin(rads),cos(rads),0,0},{0,0,1,0},{0,0,0,1}}};
}

Matrix4 translate(Vector3 translation) {
	return (Matrix4){{{1,0,0,translation.vX},{0,1,0,translation.vY},{0,0,1,translation.vZ},{0,0,0,1}}};
}

Matrix4 scale(Vector3 scalar) {
	return (Matrix4){{{scalar.vX,0,0,0},{0,scalar.vY,0,0},{0,0,scalar.vZ,0},{0,0,0,1}}};
}

Vector2 project(Vector3 v, Matrix4 proj, uint32_t width, uint32_t height) {
	Vector3 nv = transform(v,proj);
	return (Vector2){{nv.vX*width + width/2,nv.vY*height + height/2}};
}

Matrix4 lookAt(Vector3 eye, Vector3 target, Vector3 up) {
	Vector3 zaxis = normal(subtract(eye,target));
	Vector3 xaxis = normal(cross(up, zaxis));
	Vector3 yaxis = cross(zaxis, xaxis);
	return (Matrix4){{{xaxis.vX,yaxis.vX,zaxis.vX,0},{xaxis.vY,yaxis.vY,zaxis.vY,0},{xaxis.vZ,yaxis.vZ,zaxis.vZ,0},{-dot(xaxis,eye),-dot(yaxis,eye),-dot(zaxis,eye),1}}};
}


void drawPoint(Vector2 point, int16_t color) {
	screen[(int)(point.vY*WIDTH+point.vX)] = color;
}

void drawLine(Vector2 point1, Vector2 point2,int16_t color) {
	int x0 = (int)point1.vX;
  int y0 = (int)point1.vY;
	
	int x1 = (int)point2.vX;
	int y1 = (int)point2.vY;
            
	float dx = fabs(x1 - x0);
	float dy = fabs(y1 - y0);
	float sx = (x0 < x1) ? 1 : -1;
	float sy = (y0 < y1) ? 1 : -1;
	float err = dx - dy;

	while (1) {
		drawPoint((Vector2){{x0, y0}},color);

		if ((x0 == x1) && (y0 == y1)) break;
		float e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x0 += sx; }
		if (e2 < dx) { err += dx; y0 += sy; }
	}
}

float clamp(float value) {
	value = value < 1 ? value : 1;
	return value > 0 ? value : 0;
}

float interpolate(float min, float max, float gradient) {
   return min + (max - min) * clamp(gradient);
}

void drawScanline(int y, Vector2 pa, Vector2 pb, Vector2 pc, Vector2 pd, int16_t color) {
	float gradient1 = pa.vY != pb.vY ? (y - pa.vY) / (pb.vY - pa.vY) : 1;
	float gradient2 = pc.vY != pd.vY ? (y - pc.vY) / (pd.vY - pc.vY) : 1;
				 
	int sx = (int)interpolate(pa.vX, pb.vX, gradient1);
	int ex = (int)interpolate(pc.vX, pd.vX, gradient2);

	for(int x = sx; x < ex; x++) {
		drawPoint((Vector2){{x,y}},color);
	}
	/*if(ex < sx)
		ST7735_DrawFastHLine(ex, y, sx-ex, color);
	else
		ST7735_DrawFastHLine(sx, y, ex-sx, color);*/
}

void drawTriangle(Vector2 p1, Vector2 p2, Vector2 p3, int16_t color) {
	if (p1.vY > p2.vY)
	{
		Vector2 temp = p2;
		p2 = p1;
		p1 = temp;
	}
	if (p2.vY > p3.vY)
	{
		Vector2 temp = p2;
		p2 = p3;
		p3 = temp;
	}
	if (p1.vY > p2.vY)
	{
		Vector2 temp = p2;
		p2 = p1;
		p1 = temp;
	}
	
	float dP1P2, dP1P3;
	
	if (p2.vY - p1.vY > 0)
		dP1P2 = (p2.vX - p1.vX) / (p2.vY - p1.vY);
	else
		dP1P2 = 0;
	
	if (p3.vY - p1.vY > 0)
		dP1P3 = (p3.vX - p1.vX) / (p3.vY - p1.vY);
	else
		dP1P3 = 0;
	
	if (dP1P2 > dP1P3)
	{
		for (int y = (int)p1.vY; y <= (int)p3.vY; y++)
		{
			if (y < p2.vY)
				drawScanline(y, p1, p3, p1, p2, color);
			else
				drawScanline(y, p1, p3, p2, p3, color);
		}
	}
	else
	{
		for (int y = (int)p1.vY; y <= (int)p3.vY; y++)
		{
			if (y < p2.vY)
				drawScanline(y, p1, p2, p1, p3, color);
			else
				drawScanline(y, p2, p3, p1, p3, color);
		}
	}
}
