// septumfunk 2024
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <util/vector.h>
#include <util/logging.h>
#include <util/memory_safety.h>

Vector *vector_create(int element_size) {
    Vector *vector = calloc(1, sizeof(Vector));
    vector->element_size = element_size;
    return vector;
}

void vector_destroy(Vector *vector) {
    free(vector->data);
    free(vector);
}

void *vector_get(Vector *vector, unsigned int index) {
    if (index > vector->length - 1) 
        panic("Index %d is out of bounds.", index);
    return vector->data + index * vector->element_size;
}

void *vector_push(Vector *vector, void *data) {
    vector->length++;
    vector->data = realloc(vector->data, vector->element_size * vector->length);
    memcpy(vector->data + vector->element_size * (vector->length - 1), data, vector->element_size);
    return vector->data + vector->element_size * (vector->length - 1);
}

void vector_remove(Vector *vector, unsigned int index) {
    if (index > vector->length - 1) 
        panic("Index %d is out of bounds.", index);
    void *loc = vector_get(vector, index);
    memcpy(loc, loc + vector->element_size, (vector->length - 1 - index) * vector->element_size);
    vector->length--;
    vector->data = realloc(vector->data, vector->length * vector->element_size);
}