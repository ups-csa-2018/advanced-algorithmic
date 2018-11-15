#include "bheap.h"

void sort_and_get_k_first(unsigned int n, int *numbers, unsigned int k, int *result)
{
    bheap_t *heap = bheap_create(max, n, numbers, n, floyd);
    bheap_get_k_first(heap, k, result);
    bheap_destroy(heap);
}
