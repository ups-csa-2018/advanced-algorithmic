#include "bheap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool bheap_has_parent(bheap_t *heap, unsigned int index);
unsigned int bheap_parent(bheap_t *heap, unsigned int index);
bool bheap_has_left(bheap_t *heap, unsigned int index);
unsigned int bheap_left(bheap_t *heap, unsigned int index);
bool bheap_has_right(bheap_t *heap, unsigned int index);
unsigned int bheap_right(bheap_t *heap, unsigned int index);
void bheap_build_williams(bheap_t *heap, unsigned int n, value_t *numbers);
void bheap_build_floyd(bheap_t *heap, unsigned int n, value_t *numbers);
void bheap_percolate_up(bheap_t *heap, unsigned int index);
void bheap_percolate_down(bheap_t *heap, unsigned int index);
bool bheap_are_constraints_respected_i(bheap_t *heap, unsigned int i);

// binary heap
bheap_t *bheap_create(
    bheap_type_t type,
    unsigned int n,
    value_t *numbers,
    unsigned int size,
    bheap_build_type_t build_type)
{
    assert(size >= n);

    bheap_t *heap = malloc(sizeof(bheap_t));
    heap->data = malloc(sizeof(value_t) * size);
    heap->size = size;
    heap->type = type;
    heap->count = 0;

    if (build_type == williams) {
        bheap_build_williams(heap, n, numbers);
    } else {
        bheap_build_floyd(heap, n, numbers);
    }

    return heap;
}

void bheap_destroy(bheap_t *heap)
{
    assert(heap != NULL);

    free(heap->data);
    free(heap);
}

bheap_t *bheap_dup(bheap_t *heap)
{
    assert(heap != NULL);

    bheap_t *heap2 = malloc(sizeof(bheap_t));
    heap2->data = malloc(sizeof(value_t) * heap->size);
    memcpy(heap2->data, heap->data, sizeof(value_t) * heap->count);
    heap2->size = heap->size;
    heap2->type = heap->type;
    heap2->count = heap->count;

    return heap2;
}

void bheap_build_williams(bheap_t *heap, unsigned int n, value_t *numbers)
{
    for (unsigned int i = 0; i < n; i++) {
        bheap_insert(heap, numbers[i]);
    }
}

void bheap_build_floyd(bheap_t *heap, unsigned int n, value_t *numbers)
{
    memcpy(heap->data, numbers, sizeof(value_t) * n);
    heap->count = n;

    for (unsigned int i = n / 2 + 1; --i > 0;) {
        bheap_percolate_down(heap, i - 1);
    }
}

bool bheap_has_parent(bheap_t *heap, unsigned int index)
{
    return index != 0 && (index - 1) / 2 < heap->count;
}

unsigned int bheap_parent(bheap_t *heap, unsigned int index)
{
    assert(bheap_has_parent(heap, index));

    return (index - 1) / 2;
}

bool bheap_has_left(bheap_t *heap, unsigned int index)
{
    return index * 2 + 1 < heap->count;
}

unsigned int bheap_left(bheap_t *heap, unsigned int index)
{
    assert(bheap_has_left(heap, index));

    return index * 2 + 1;
}

bool bheap_has_right(bheap_t *heap, unsigned int index)
{
    return index * 2 + 2 < heap->count;
}

unsigned int bheap_right(bheap_t *heap, unsigned int index)
{
    assert(bheap_has_right(heap, index));

    return index * 2 + 2;
}

void bheap_insert(bheap_t *heap, value_t value)
{
    assert(heap != NULL);
    assert(heap->size > heap->count);

    heap->data[heap->count] = value;
    heap->count++;

    bheap_percolate_up(heap, heap->count - 1);
}

void bheap_remove(bheap_t *heap, unsigned int index)
{
    assert(heap != NULL);
    assert(index < heap->count);

    heap->data[index] = heap->data[heap->count - 1];
    heap->count--;

    // We actually need to percolate up OR down depending on where was the
    // node we removed. But since percolate is a NO-OP (or O(1)) if it is too
    // deep or too high in the tree then we do both percolate.
    bheap_percolate_up(heap, index);
    bheap_percolate_down(heap, index);
}

void bheap_percolate_up(bheap_t *heap, unsigned int index)
{
    while (1) {
        if (!bheap_has_parent(heap, index)) {
            return;
        }

        value_t value = heap->data[index];
        unsigned int parent_index = bheap_parent(heap, index);
        value_t parent_value = heap->data[parent_index];

        if (heap->type == max && value <= parent_value) {
            return;
        }

        if (heap->type == min && value >= parent_value) {
            return;
        }

        heap->data[index] = parent_value;
        heap->data[parent_index] = value;
        index = parent_index;
    }
}

void bheap_percolate_down(bheap_t *heap, unsigned int index)
{
    while (1) {
        value_t value = heap->data[index];

        if (!bheap_has_left(heap, index)) {
            return;
        }

        unsigned int child_index = bheap_left(heap, index);
        value_t child_value = heap->data[child_index];

        if (bheap_has_right(heap, index)) {
            unsigned int right_index = bheap_right(heap, index);
            value_t right_value = heap->data[right_index];

            if ((heap->type == max && right_value >= child_value)
                || (heap->type == min && right_value <= child_value)) {
                child_index = right_index;
                child_value = right_value;
            }
        }

        if ((heap->type == max && value >= child_value)
            || (heap->type == min && value <= child_value)) {
            break;
        }

        heap->data[index] = child_value;
        heap->data[child_index] = value;
        index = child_index;
    }
}

void bheap_get_k_first(bheap_t *heap, unsigned int k, value_t *result)
{
    assert(k <= heap->count);

    bheap_t *h = bheap_dup(heap);

    for (unsigned int i = 0; i < k; i++) {
        result[i] = h->data[0];
        bheap_remove(h, 0);
    }

    bheap_destroy(h);
}

void bheap_debug_print(bheap_t *heap)
{
    assert(heap != NULL);

    printf("heap data: ");

    for (unsigned int i = 0; i < heap->count; i++) {
        printf("%u ", heap->data[i]);
    }

    printf("\n");
}

bool bheap_are_constraints_respected(bheap_t *heap)
{
    assert(heap != NULL);

    return bheap_are_constraints_respected_i(heap, 0);
}
bool bheap_are_constraints_respected_i(bheap_t *heap, unsigned int i)
{
    value_t value = heap->data[i];

    bool left_respected = true;
    bool right_respected = true;

    if (bheap_has_right(heap, i)) {
        value_t right_value = heap->data[bheap_right(heap, i)];
        if ((heap->type == max && value < right_value)
            || (heap->type == min && value > right_value)) {
            return false;
        }

        right_respected = bheap_are_constraints_respected_i(heap, bheap_right(heap, i));
    }

    if (bheap_has_left(heap, i)) {
        value_t left_value = heap->data[bheap_left(heap, i)];
        if ((heap->type == max && value < left_value)
            || (heap->type == min && value > left_value)) {
            return false;
        }

        left_respected = bheap_are_constraints_respected_i(heap, bheap_left(heap, i));
    }

    return left_respected && right_respected;
}
