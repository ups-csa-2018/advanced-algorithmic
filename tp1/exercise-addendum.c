#include "bheap.h"
#include <assert.h>
#include <stdlib.h>

void heap_sort(unsigned int n, value_t *numbers, value_t *result)
{
    bheap_t *heap = bheap_create(max, n, numbers, n, floyd);
    bheap_get_k_first(heap, n, result);
    bheap_destroy(heap);
}

// heap sort
void sort_and_get_k_first(unsigned int n, int *numbers, unsigned int k, int *result)
{
    value_t *heap_sort_result = malloc(sizeof(value_t) * n);
    heap_sort(n, numbers, heap_sort_result);

    for (unsigned int i = 0; i < k; i++) {
        result[i] = heap_sort_result[i];
    }

    free(heap_sort_result);
}
