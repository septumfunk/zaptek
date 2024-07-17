#include <graphics/display.h>
#include <stdio.h>
#include "input/keyboard.h"
#include "io/files.h"
#include "util/vector.h"

int main() {
    Display display = create_display("Test Window", 800, 600);
    while (display_loop(&display)) {

       display_swap(&display);
    }
    return 0;
}