#pragma once
#include <stddef.h>

typedef struct vector {
    void *arr;
    uintarch_t count, size, cap;
} vector_t;

vector_t vector_init(uintarch_t size);
void vector_push_back(vector_t *this, void *item);
void vector_pop(vector_t *this);
void *vector_get(vector_t *this, uintarch_t index);
void vector_destroy(vector_t *this);
