#include "camera.h"
#include "vec2.h"

Camera cam = {0};

void Camera_set(Vec2 position) {
    cam = position;
}

Vec2 Camera_get() {
    return cam;
}
