#include <stdint.h>
#define vX V[0]
#define vY V[1]
#define vZ V[2]
#define vW V[3]
struct Matrix4 {
	float M[4][4];
};
typedef struct Matrix4 Matrix4;

struct Vector4 {
	float V[4];
};
typedef struct Vector4 Vector4;

struct Vector3 {
	float V[3];
};
typedef struct Vector3 Vector3;

struct Vector2 {
	float V[2];
};
typedef struct Vector2 Vector2;


Matrix4 multiply(Matrix4 m, Matrix4 m2);
Vector3 transform(Vector3 v3, Matrix4 m);
void print(Matrix4 m);
Vector3 normal(Vector3 p);
float dot(Vector3 a, Vector3 b);
Vector3 cross(Vector3 a, Vector3 b);
Vector3 subtract(Vector3 a,Vector3 b);
Vector3 add(Vector3 a,Vector3 b);
