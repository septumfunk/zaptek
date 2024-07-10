#include <graphics/display.h>

int main() {
    zt_display display = zt_display_create("Test Window", 800, 600);
    while (zt_display_loop(&display)) {
        zt_display_swap(&display);
    }
    return 0;
}