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
	Vector4 v = {{(v3).V[0],(v3).V[1],(v3).V[2],1}};
	Vector4 o;
	for(int r = 0; r < 4; r++) {
		o.V[r] = 0;
		for(int c = 0; c < 4; c++) {
			o.V[r] += m.M[c][r] * v.V[c];
		}
	}
	
	return (Vector3){{o.V[0]/o.V[3],o.V[1]/o.V[3],o.V[2]/o.V[3]}};
}


Vector3 normal(Vector3 p) {
	float w = sqrt(p.V[0]*p.V[0]+p.V[1]*p.V[1]+p.V[2]*p.V[2]);
	return (Vector3){{p.V[0]/w,p.V[1]/w,p.V[2]/w}};
}

float dot(Vector3 a, Vector3 b) {
	return a.V[0]*b.V[0]+a.V[1]*b.V[1]+a.V[2]*b.V[2];
}

Vector3 cross(Vector3 a, Vector3 b) {
  return (Vector3){{a.V[1]*b.V[2]-a.V[2]*b.V[1],a.V[2]*b.V[0]-a.V[0]*b.V[2],a.V[0]*b.V[1]-a.V[1]*b.V[0]}};
}

Vector3 subtract(Vector3 a,Vector3 b) {
	return (Vector3){{a.V[0]-b.V[0],a.V[1]-b.V[1],a.V[2]-b.V[2]}};
}
