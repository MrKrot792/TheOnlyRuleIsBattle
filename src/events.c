#include "events.h"
#include "character.h"
#include "app.h"

#include <ncurses.h>

void Events_pollEvents() {
    int ch = getch();

    switch (ch) {
        case 'a':
            *Character_getX() -= 1;
            break;
        case 'd':
            *Character_getX() += 1;
            break;
        case 'w':
            *Character_getY() -= 1;
            break;
        case 's':
            *Character_getY() += 1;
            break;

        case 'q':
            App_break(APP_OK);
            break;
    }
}
