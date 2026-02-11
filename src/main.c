#include <stdio.h>
#include "app.h"

int main() {
    App_init();
    int error = App_loop();
    App_deinit();

    if (error != APP_OK) {
        if (App_isErrorMessagePresent())
        fprintf(stderr, "ERROR: The app returned an error: %d\nMessage: %s\n", error, App_errno());
        else 
        fprintf(stderr, "ERROR: The app returned an error: %d", error);
    }
    return error;
}
