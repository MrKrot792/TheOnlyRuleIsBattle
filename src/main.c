#include <stdio.h>
#include "app.h"

int main() {
    App_init();
    int error = App_loop();
    App_deinit();

    if (error != APP_OK) fprintf(stderr, "ERROR: The app returned an error: %d\n", error);
    return error;
}
