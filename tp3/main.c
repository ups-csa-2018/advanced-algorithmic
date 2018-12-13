#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "ubqp.h"
#include "vector.h"

void usage()
{
    fprintf(stderr, "Usage: ./ubqp max-attempts\n");
}

int main(int argc, char **argv)
{
    int **matrix_data;
    unsigned int n;
    int p;
    unsigned int max_attempts;
    matrix_t *matrix;

    srand(time(NULL));

    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    if (1 != sscanf(argv[1], "%u", &max_attempts)) {
        usage();
        exit(EXIT_FAILURE);
    }

    if (1 != scanf("%u", &n)) {
        fprintf(stderr, "Unable to read the matrix size.\n");

        exit(EXIT_FAILURE);
    }

    if (1 != scanf("%d", &p)) {
        fprintf(stderr, "Unable to read this p number.\n");

        exit(EXIT_FAILURE);
    }

    matrix_data = malloc(sizeof(int *) * n);
    for (unsigned int i = 0; i < n; i++) {
        matrix_data[i] = malloc(sizeof(int) * n);
        for (unsigned int j = 0; j < n; j++) {
            if (1 != scanf("%d", &matrix_data[i][j])) {
                fprintf(stderr, "Unable to read the matrix num %u, %u.\n", i, j);

                exit(EXIT_FAILURE);
            }
        }
    }

    matrix = matrix_create(matrix_data, n);

    for (unsigned int i = 0; i < n; i++) {
        free(matrix_data[i]);
    }

    free(matrix_data);

    vector_t *best_var = ubqp_rnd_hill_climb(matrix, max_attempts);

    vector_print(best_var);
    printf("%d\n", ubqp_get_value(matrix, best_var));

    vector_destroy(best_var);
    matrix_destroy(matrix);

    exit(EXIT_SUCCESS);
}
