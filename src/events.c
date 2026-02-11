#include "events.h"
#include "character.h"
#include "app.h"
#include "vec2.h"

#include <ncurses.h>

void Events_pollEvents() {
    int ch = getch();

    Vec2 movement_vector = Vec2_zero();

    switch (ch) {
        case 'a':
            movement_vector.x = -1;
            break;
        case 'd':
            movement_vector.x = 1;
            break;
        case 'w':
            movement_vector.y = -1;
            break;
        case 's':
            movement_vector.y = 1;
            break;
        case 'q':
            App_break(APP_OK);
            break;
    }

    if (!Vec2_isZero(movement_vector)) {
        Character_setPosition(Vec2_add(Character_getPosition(), movement_vector));
    }
}
