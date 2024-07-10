// septumfunk 2024
#pragma once
#include <graphics/opengl.h>

/// A shader's structure. Contains the individual shaders, and their program.
typedef struct zt_shader {
    GLuint program;
    GLuint vertex;
    GLuint fragment;
} zt_shader;

/// Creates a Zaptek shader struct.
/// This struct uses dynamic memory allocation. Please remember to call the corresponding cleanup method.
zt_shader zt_shader_create();