// septumfunk 2024
#include <graphics/shader.h>
#include <io/files.h>
#include <graphics/opengl.h>
#include <string.h>
#include <util/logging.h>
#include <util/memory_safety.h>

/// Loads a shader file. For internal use of shader.
static inline GLuint load_shader_file(int type, const char *path) {
    GLuint shader = glCreateShader(type);

    // Source
    const char *source = quickload(path);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Error Checking
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        panic("Shader \"%s\"failed to compile!\n%s\n", path, log);
    }

    return shader;
}

/// Links a vertex and fragment shader. For internal use of shader.
static inline GLuint link_shaders(GLuint vertex, GLuint fragment) {
    GLuint program = glCreateProgram();

    // Linking
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    // Error Checking
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, NULL, log);
        panic("Program failed to link!\n%s\n", log);
    }

    return program;
}

Shader create_shader(const char *shader_name) {
    Shader shader = {0};

    // Vertex
    char path[strlen(shader_name) + strlen("data/shaders/.vert") + 1];
    snprintf(path, sizeof(path), "data/shaders/%s.vert", shader_name);
    char *vert = quickload(path);
    nullsafe(vert);
    printf("## Vertex Shader \"%s\":\n%s\n\n", shader_name, vert);
    shader.vertex = load_shader_file(GL_VERTEX_SHADER, vert);
    free(vert);

    // Fragment
    snprintf(path, sizeof(path), "data/shaders/%s.frag", shader_name);
    char *frag = quickload(path);
    nullsafe(frag);
    printf("## Fragment Shader \"%s\":\n%s\n\n", shader_name, frag);
    shader.fragment = load_shader_file(GL_FRAGMENT_SHADER, frag);
    free(frag);

    shader.program = link_shaders(shader.vertex, shader.fragment);

    return shader;
}

void destroy_shader(Shader shader) {
    glDeleteShader(shader.vertex);
    glDeleteShader(shader.fragment);
    glDeleteProgram(shader.program);
}