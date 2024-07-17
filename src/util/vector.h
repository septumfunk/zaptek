// septumfunk 2024
#pragma once

/// Simple generic-esque vector implementation.
typedef struct Vector {
    void *data;
    int length;
    int element_size;
} Vector;

/// Creates a Vector, or dynamic array.
/// This function allocates on the heap. Please ensure to call its matching cleanup when it's no longer needed! 
Vector *vector_create(int element_size);

/// Destroys a Vector and all of its elements.
void vector_destroy(Vector *vector);

/// Gets vector value at specified index.
/// Please cast this to the desired type.
void *vector_get(Vector *vector, unsigned int index);

/// Pushes an element to the end of the vector.
void *vector_push(Vector *vector, void *data);

/// Removes a vector element at the specified index.
void vector_remove(Vector *vector, unsigned int index);