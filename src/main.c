#include <stdio.h>
#include "app.h"

int main() {
    App_init();
    // Looping until an error or `running = false`
    int error = App_loop();
    if (error != APP_OK) fprintf(stderr, "ERROR: The app returned an error: %d\n", error);
    App_deinit();
    return error;
}
