#include "Matrix.h"
#include "print.h"
#include "ST7735.h"
#include <math.h>

Matrix4 multiply(Matrix4 m1, Matrix4 m2) {
	Matrix4 o;
	
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			o.M[r][c] = 0;
			for(int i = 0; i < 4; i++) {
				o.M[r][c] += m1.M[r][i]*m2.M[i][c];
			}
		}
	}
	
	return o;
}

void print(Matrix4 m) {
	for(int r = 0; r < 4; r++) {
		for(int c = 0; c < 4; c++) {
			LCD_OutDec(m.M[r][c]);
			ST7735_OutChar(' ');
		}
		ST7735_OutChar('\n');
	}
}

Vector3 transform(Vector3 v3, Matrix4 m) {
	Vector4 v = {{(v3).vX,(v3).vY,(v3).vZ,1}};
	Vector4 o;
	for(int r = 0; r < 4; r++) {
		o.V[r] = 0;
		for(int c = 0; c < 4; c++) {
			o.V[r] += m.M[c][r] * v.V[c];
		}
	}
	
	return (Vector3){{o.vX/o.vW,o.vY/o.vW,o.vZ/o.vW}};
}


Vector3 normal(Vector3 p) {
	float w = sqrt(p.vX*p.vX+p.vY*p.vY+p.vZ*p.vZ);
	return (Vector3){{p.vX/w,p.vY/w,p.vZ/w}};
}

float dot(Vector3 a, Vector3 b) {
	return a.vX*b.vX+a.vY*b.vY+a.vZ*b.vZ;
}

Vector3 cross(Vector3 a, Vector3 b) {
  return (Vector3){{a.vY*b.vZ-a.vZ*b.vY,a.vZ*b.vX-a.vX*b.vZ,a.vX*b.vY-a.vY*b.vX}};
}

Vector3 subtract(Vector3 a,Vector3 b) {
	return (Vector3){{a.vX-b.vX,a.vY-b.vY,a.vZ-b.vZ}};
}

Vector3 add(Vector3 a,Vector3 b) {
	return (Vector3){{a.vX+b.vX,a.vY+b.vY,a.vZ+b.vZ}};
}
