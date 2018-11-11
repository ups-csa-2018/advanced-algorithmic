// bubble sort
void sort_and_get_k_first(unsigned int n, int *numbers, unsigned int k, int *result)
{
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = i; j < n; j++) {
            if (numbers[i] < numbers[j]) {
                int t = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = t;
            }
        }

        result[i] = numbers[i];

        if (i > k) {
            break;
        }
    }
}
