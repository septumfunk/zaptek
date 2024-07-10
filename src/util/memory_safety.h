// septumfunk 2024
#pragma once

#define nullsafe(pointer) \
if (pointer == NULL) { \
    fprintf(stderr, "Pointer %s is NULL.\n", #pointer); \
    exit(-1); \
}