#include <stdio.h>
#include <stdlib.h>

void sort_and_get_k_first(unsigned int n, int *numbers, unsigned int k, int *result);

int get_input(FILE *file, unsigned int *n, unsigned int *k, int **numbers)
{
    if (1 != fscanf(file, "%u", n)) {
        fprintf(stderr, "Unable to read the `n` number.\n");

        return 0;
    }

    if (1 != fscanf(file, "%u", k)) {
        fprintf(stderr, "Unable to read the `k` number.\n");

        return 0;
    }

    *numbers = malloc(sizeof(int) * *n);

    for (unsigned int i = 0; i < *n; i++) {
        if (1 != fscanf(file, "%d", (*numbers + i))) {
            fprintf(stderr, "Unable to read the number #%d.\n", i);

            return 0;
        }
    }

    return 1;
}

int main(int argc, char **argv)
{
    unsigned int n;
    unsigned int k;
    int *numbers = NULL;
    FILE *file = stdin;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [file]\n", argv[0]);

        exit(EXIT_FAILURE);
    }

    if (argc > 1) {
        if (NULL == (file = fopen(argv[1], "r+"))) {
            perror("Unable to open the input file.");

            exit(EXIT_FAILURE);
        }
    }

    if (!get_input(file, &n, &k, &numbers)) {
        exit(EXIT_FAILURE);
    }

    int *result = malloc(sizeof(int) * k);

    sort_and_get_k_first(n, numbers, k, result);

    for (unsigned int i = 0; i < k; i++) {
        printf("%d%c", result[i], (i == k - 1) ? '\n' : ' ');
    }

    free(result);
    free(numbers);
    fclose(file);

    exit(EXIT_SUCCESS);
}
