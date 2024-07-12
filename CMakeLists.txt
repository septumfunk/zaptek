cmake_minimum_required(VERSION 3.29)
project(zaptek)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_COMPILER clang)

add_executable(${PROJECT_NAME}
    src/main.c

    src/graphics/display.c

    src/input/keyboard.c
)
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(cglm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    glad::glad
    cglm::cglm
    glfw
)