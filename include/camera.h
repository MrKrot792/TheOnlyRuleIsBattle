#include "vec2.h"

// Camera, just an alias
typedef Vec2 Camera;

// New camera's position is `CameraPosition + offset`
void Camera_translate(Vec2 offset);
Vec2 Camera_get();
