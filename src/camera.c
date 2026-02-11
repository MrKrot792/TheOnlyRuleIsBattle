#include "camera.h"
#include "vec2.h"

Camera cam = {0};

void Camera_translate(Vec2 offset) {
    cam = Vec2_add(cam, offset);
}

Vec2 Camera_get() {
    return cam;
}
