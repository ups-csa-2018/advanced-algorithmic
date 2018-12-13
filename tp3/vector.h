#pragma once

#include <stdbool.h>

typedef struct {
    bool *data;
    unsigned int size;
} vector_t;

vector_t *vector_create(bool *data, unsigned int size);
vector_t *vector_create_rnd(unsigned int size);
vector_t *vector_dup(const vector_t *vector);
void vector_flip(vector_t *vector, unsigned int index);
bool vector_get(const vector_t *vector, unsigned int index);
void vector_destroy(vector_t *vector);
void vector_print(const vector_t *vector);
