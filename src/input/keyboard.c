// septumfunk 2024
#include <input/keyboard.h>
#include <string.h>

void glfw_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
        keys_pressed[key] = true;
    if (action == GLFW_RELEASE)
        keys_pressed[key] = false;
}

bool zt_is_key_pressed(key key) {
    return keys_pressed[key];
}

bool zt_is_key_down(GLFWwindow *handle, key key) {
    return glfwGetKey(handle, key) == GLFW_PRESS;
}

void zt_keys_reset() {
    memset(keys_pressed, 0, KEY_COUNT);
}