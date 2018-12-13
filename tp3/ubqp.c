#include <stddef.h>
#include "ubqp.h"

#define MAX_MOVES 10000

int ubqp_get_value(const matrix_t *matrix, const vector_t *variable)
{
    int sum = 0;

    for (unsigned int i = 0; i < matrix->size; i++) {
        for (unsigned int j = 0; j < matrix->size; j++) {
            sum += matrix->data[i][j] * variable->data[i] * variable->data[j];
        }
    }

    return sum;
}

vector_t *ubqp_get_best_neighbour(const matrix_t *matrix, const vector_t *variable)
{
    vector_t *best_neighbour = vector_dup(variable);
    int best_sum = ubqp_get_value(matrix, best_neighbour);

    for (unsigned int i = 0; i < matrix->size; i++) {
        vector_t *neighbour = vector_dup(variable);
        vector_flip(neighbour, i);
        int sum = ubqp_get_value(matrix, variable);

        if (sum < best_sum) {
            vector_destroy(best_neighbour);
            best_neighbour = vector_dup(neighbour);
            best_sum = sum;
        }

        vector_destroy(neighbour);
    }

    return best_neighbour;
}

vector_t* ubqp_hill_climb(const matrix_t *matrix, const vector_t *variable)
{
    vector_t *best_variable = vector_dup(variable);
    int best_sum = ubqp_get_value(matrix, variable);

    for (unsigned int i = 0; i < MAX_MOVES; i++) {
        vector_t *best_neighbour = ubqp_get_best_neighbour(matrix, variable);
        int sum = ubqp_get_value(matrix, variable);

        vector_destroy(best_variable);
        best_variable = best_neighbour;

        if (best_sum == sum) {
            break;
        }
    }

    return best_variable;
}

vector_t *ubqp_rnd_hill_climb(const matrix_t *matrix, unsigned int max_attempts)
{
    vector_t *global_best_var = NULL;
    int global_best_sum = 0;

    for (unsigned int i = 0; i < max_attempts; i++) {
        vector_t *rnd_var = vector_create_rnd(matrix->size);
        vector_t *local_best_var = ubqp_hill_climb(matrix, rnd_var);
        int local_best_sum = ubqp_get_value(matrix, local_best_var);

        if (global_best_var == NULL || local_best_sum < global_best_sum) {
            if (global_best_var != NULL) {
                vector_destroy(global_best_var);
            }

            global_best_var = vector_dup(local_best_var);
            global_best_sum = local_best_sum;
        }

        vector_destroy(local_best_var);
        vector_destroy(rnd_var);
    }

    return global_best_var;
}
