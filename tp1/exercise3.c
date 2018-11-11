#include <stdlib.h>
#include <string.h>

// quick sort
int cmp_fn(const void *p1, const void *p2)
{
    return *(int *)p1 < *(int *)p2;
}

void sort_and_get_k_first(unsigned int n, int *numbers, unsigned int k, int *result)
{
    int *sorted_numbers = malloc(sizeof(int) * n);
    memcpy(sorted_numbers, numbers, sizeof(int) * n);
    qsort(sorted_numbers, n, sizeof(int), cmp_fn);

    for (unsigned int i = 0; i < k; i++) {
        result[i] = sorted_numbers[i];
    }

    free(sorted_numbers);
}
