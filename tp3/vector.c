#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector_t *vector_create(bool *data, unsigned int size)
{
    vector_t *vector = malloc(sizeof(vector_t));
    vector->data = malloc(sizeof(int) * size);
    vector->size = size;

    for (unsigned int i = 0; i < size; i++) {
        vector->data[i] = data[i];
    }

    return vector;
}

vector_t *vector_create_rnd(unsigned int size)
{
    bool *data = malloc(sizeof(data) * size);

    for (unsigned int i = 0; i < size; i++) {
        data[i] = rand() % 2;
    }

    vector_t *vector = vector_create(data, size);
    free(data);

    return vector;
}

vector_t *vector_dup(const vector_t *vector)
{
    return vector_create(vector->data, vector->size);
}

void vector_flip(vector_t *vector, unsigned int index)
{
    vector->data[index] = !vector->data[index];
}

bool vector_get(const vector_t *vector, unsigned int index)
{
    return vector->data[index];
}

void vector_destroy(vector_t *vector)
{
    free(vector->data);
    free(vector);
}

void vector_print(const vector_t *vector)
{
    for (unsigned int i = 0; i < vector->size; i++) {
        printf("%s%d", i == 0 ? "" : " ", vector->data[i]);
    }

    printf("\n");
}
