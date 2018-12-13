#pragma once

#include "matrix.h"
#include "vector.h"

int ubqp_get_value(const matrix_t *matrix, const vector_t *variable);
vector_t *ubqp_get_best_neighbour(const matrix_t *matrix, const vector_t *variable);
vector_t* ubqp_hill_climb(const matrix_t *matrix, const vector_t *variable);
vector_t *ubqp_rnd_hill_climb(const matrix_t *matrix, unsigned int max_attempts);
