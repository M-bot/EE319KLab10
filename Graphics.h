Matrix4 ortho(float width, float height, float zfar, float znear);
Vector2 project(Vector3 v, Matrix4 proj, uint32_t width, uint32_t height);
Matrix4 rotate(float degrees, int axis);
Matrix4 translate(Vector3 translation);
Matrix4 scale(Vector3 scalar);
void drawPoint(Vector2 point, int16_t color);
void drawLine(Vector2 point1, Vector2 point2, int16_t color);
Matrix4 lookAt(Vector3 eye, Vector3 target, Vector3 up);
Matrix4 pers(float fovx, float fovy, float zfar, float znear);
