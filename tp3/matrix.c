#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

matrix_t *matrix_create(int **data, unsigned int size)
{
    matrix_t *matrix = malloc(sizeof(matrix_t));
    matrix->data = malloc(sizeof(int *) * size);
    matrix->size = size;

    for (unsigned int i = 0; i < size; i++) {
        matrix->data[i] = malloc(sizeof(int) * size);

        for (unsigned int j = 0; j < size; j++) {
            matrix->data[i][j] = data[i][j];
        }
    }

    return matrix;
}

void matrix_destroy(matrix_t *matrix)
{
    for (unsigned int i = 0; i < matrix->size; i++) {
        free(matrix->data[i]);
    }

    free(matrix);
}

void matrix_print(const matrix_t *matrix)
{
    for (unsigned int i = 0; i < matrix->size; i++) {
        for (unsigned int j = 0; j < matrix->size; j++) {
            printf("%s%5d", j == 0 ? "" : " ", matrix->data[i][j]);
        }

        printf("\n");
    }
}
