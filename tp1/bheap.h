#pragma once

#include <stdbool.h>

typedef enum {
    min,
    max
} bheap_type_t;

typedef enum {
    williams,
    floyd
} bheap_build_type_t;

typedef int value_t;

typedef struct {
    value_t *data;
    unsigned int size;
    unsigned int count;
    bheap_type_t type;
} bheap_t;

bheap_t *bheap_create(
    bheap_type_t type,
    unsigned int n,
    value_t *numbers,
    unsigned int size,
    bheap_build_type_t build_type);
bheap_t *bheap_dup(bheap_t *heap);
void bheap_destroy(bheap_t *heap);
void bheap_insert(bheap_t *heap, value_t value);
void bheap_remove(bheap_t *heap, unsigned int index);
void bheap_get_k_first(bheap_t *heap, unsigned int k, value_t *result);
void bheap_debug_print(bheap_t *heap);
bool bheap_are_constraints_respected(bheap_t *heap);
