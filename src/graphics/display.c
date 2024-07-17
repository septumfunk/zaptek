// septumfunk 2024
#include <graphics/display.h>
#include <graphics/opengl.h>
#include <util/memory_safety.h>
#include <util/logging.h>
#include <input/keyboard.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Display create_display(const char *title, int width, int height) {
    Display display;
    // Display Title
    int title_len = strlen(title) * sizeof(char) + 1;
    if (title_len > 255)
        panic("Title \"%s\" is too long! Zaptek supports a max title of 255 characters.", title);
    strcpy_s(display.title, title_len, title);

    // Dimensions
    display.dimensions[0] = width;
    display.dimensions[1] = height;

    if (!glfwInit())
        panic("Failed to initialize GLFW!");

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Will be displayed when ready.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    display.handle = glfwCreateWindow(width, height, title, NULL, NULL);
    nullsafe(display.handle);
    glfwSetErrorCallback(display_glfw_error);
    glfwSetKeyCallback(display.handle, glfw_keyboard_callback);

    const GLFWvidmode *vmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    nullsafe(vmode);

    glfwSetWindowPos(
            display.handle,
            (vmode->width - height) / 2,
            (vmode->height - width) / 2
    );

    glfwMakeContextCurrent(display.handle);
    gladLoadGL();
    glfwSwapInterval(0); // Disable V-Sync
    glfwShowWindow(display.handle);

    //glm::mat4 projection = glm::perspective(45.0f, dimensions.x / dimensions.y, -100.0f, 100.0f);
    return display;
}

void destroy_display(Display *display) {
    free(display->title);
}

bool display_loop(Display *display) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return !glfwWindowShouldClose(display->handle);
}

void display_swap(Display *display) {
    glfwSwapBuffers(display->handle);
    keys_reset();
    glfwPollEvents();

    if (is_key_pressed(KEY_ESCAPE))
        glfwSetWindowShouldClose(display->handle, true);
}

void display_resize(Display *display, int width, int height) {
    glfwSetWindowSize(display->handle, width, height);
    glViewport(0, 0, width, height);
}

void display_glfw_error(int error_code, const char* description) {
    fprintf(stderr, "OpenGL Error (Code %d):\n%s.", error_code, description);
}