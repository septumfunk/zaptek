// septumfunk 2024
#pragma once
#include <graphics/opengl.h>

/// A shader's structure. Contains the individual shaders, and their program.
typedef struct Shader {
    GLuint program;
    GLuint vertex;
    GLuint fragment;
} Shader;

/// Creates a Zaptek shader struct.
/// This struct uses dynamic memory allocation. Please remember to call the corresponding cleanup method.
Shader create_shader(const char *path);

/// Destroys a Zaptek shader struct.
/// Clears dynamic memory.
void destroy_shader(Shader shader);