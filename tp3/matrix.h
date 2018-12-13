#pragma once

typedef struct {
    int **data;
    unsigned int size;
} matrix_t;

matrix_t *matrix_create(int **data, unsigned int size);
void matrix_destroy(matrix_t *matrix);
void matrix_print(const matrix_t *matrix);
