// septumfunk 2024
#pragma once
#include <cglm/types.h>
#include <graphics/opengl.h>
#include <stdbool.h>

/// Display states enum. Determines whether a display is ready to draw or not.
typedef enum zt_display_state {
    ZT_DISPLAY_UNINITIALIZED, /// Display is not ready to draw, GLFW3 has not been initialized.
    ZT_DISPLAY_HIDDEN, /// Display is hidden. Do not draw to displays while they are hidden.
    ZT_DISPLAY_READY, /// Display is ready and raring to go!
} zt_display_state;

/// Display data structure. Contains necessary information about the OpenGL window.
typedef struct zt_display {
    GLFWwindow *handle; /// The OpenGL window's handle.
    zt_display_state state; /// State determining whether a display is ready to draw or not.
    
    char title[255]; /// A cstring representation of the display's title.
    vec2 dimensions; /// The width and height of the display.
} zt_display;

/// Constructs a new zt_display with the specified title and dimensions.
zt_display zt_display_create(const char *title, int width, int height);

/// Cleans up the dynamically allocated resources used by a display.
void zt_display_cleanup(zt_display *display);

/// Sets up rendering and checks if the window should be closed. It should be called as the condition of a while loop.
bool zt_display_loop(zt_display *display);

/// Completes rendering and swaps the display buffers. This should be called at the absolute end of every frame.
void zt_display_swap(zt_display *display);

/// Resized display and updates glViewport.
void zt_display_resize(zt_display *display, int width, int height);

/// Handles GLFW errors.
void zt_display_glfw_error(int error_code, const char* description);