#include <stdlib.h>
#include <string.h>

// bubble sort
void sort_and_get_k_first(unsigned int n, int *numbers, unsigned int k, int *result)
{
    int *sorted_numbers = malloc(sizeof(int) * n);
    memcpy(sorted_numbers, numbers, sizeof(int) * n);

    for (unsigned int i = 0; i < k; i++) {
        for (unsigned int j = 0; j + 1 < n - i; j++) {
            if (sorted_numbers[j] > sorted_numbers[j + 1]) {
                int t = sorted_numbers[j];
                sorted_numbers[j] = sorted_numbers[j + 1];
                sorted_numbers[j + 1] = t;
            }
        }

        result[i] = sorted_numbers[n - 1 - i];

        if (i == k) {
            break;
        }
    }

    free(sorted_numbers);
}
