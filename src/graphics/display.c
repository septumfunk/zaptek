// septumfunk 2024
#include <graphics/display.h>
#include <graphics/opengl.h>
#include <util/memory_safety.h>
#include <input/keyboard.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

zt_display zt_display_create(const char *title, int width, int height) {
    zt_display display;
    // Display Title
    int title_len = strlen(title) * sizeof(char) + 1;
    if (title_len > 255) {
        fprintf(stderr, "Title \"%s\" is too long! Zaptek supports a max title of 255 characters.", title);
        exit(-1);
    }
    strcpy_s(display.title, title_len, title);

    // Dimensions
    display.dimensions[0] = width;
    display.dimensions[1] = height;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to Initialize GLFW!");
        exit(-1);
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // Will be displayed when ready.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    display.handle = glfwCreateWindow(width, height, title, NULL, NULL);
    nullsafe(display.handle);
    glfwSetErrorCallback(zt_display_glfw_error);
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

void zt_display_cleanup(zt_display *display) {
    free(display->title);
}

bool zt_display_loop(zt_display *display) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return !glfwWindowShouldClose(display->handle);
}

void zt_display_swap(zt_display *display) {
    glfwSwapBuffers(display->handle);
    zt_keys_reset();
    glfwPollEvents();

    if (zt_is_key_pressed(KEY_ESCAPE))
        glfwSetWindowShouldClose(display->handle, true);
}

void zt_display_resize(zt_display *display, int width, int height) {
    glfwSetWindowSize(display->handle, width, height);
    glViewport(0, 0, width, height);
}

void zt_display_glfw_error(int error_code, const char* description) {
    fprintf(stderr, "OpenGL Error (Code %d):\n%s.", error_code, description);
}