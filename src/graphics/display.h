// septumfunk 2024
#pragma once
#include <cglm/types.h>
#include <graphics/opengl.h>
#include <stdbool.h>

/// Display data structure. Contains necessary information about the OpenGL window.
typedef struct Display {
    GLFWwindow *handle; /// The OpenGL window's handle.    
    char title[255]; /// A cstring representation of the display's title.
    vec2 dimensions; /// The width and height of the display.
} Display;

/// Constructs a new Display with the specified title and dimensions.
Display create_display(const char *title, int width, int height);

/// Cleans up the dynamically allocated resources used by a display.
void destroy_display(Display *display);

/// Sets up rendering and checks if the window should be closed. It should be called as the condition of a while loop.
bool display_loop(Display *display);

/// Completes rendering and swaps the display buffers. This should be called at the absolute end of every frame.
void display_swap(Display *display);

/// Resized display and updates glViewport.
void display_resize(Display *display, int width, int height);

/// Handles GLFW errors.
void display_glfw_error(int error_code, const char* description);