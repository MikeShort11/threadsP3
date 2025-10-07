#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int trial_division_helper(int dividend) {
    int limit = sqrt(dividend);
    for (int divisor = 2; divisor <= limit; divisor++) {
        if ((dividend % divisor) == 0) {
            return divisor;
        }
    }
    return 0;
}

void* trial_division(void* arg) {
    int number = *(int*)arg;
    int* result = malloc(10 * sizeof(int)); // max 10 factors
    int factor_counter = 0;
    int factor;

    while ((factor = trial_division_helper(number)) != 0) {
        result[factor_counter++] = factor;
        number /= factor;
    }
    if (number > 1) {
        result[factor_counter++] = number;
    }
    result[factor_counter] = 0;
    return result;
}

int main() {
    int arr[25];
    for (int i = 0; i < 25; i++) {
        scanf("%d", &arr[i]);
    }

    int length = sizeof(arr) / sizeof(arr[0]);
    pthread_t* threads = malloc(length * sizeof(pthread_t));

    for (int i = 0; i < length; i++) {
        pthread_create(&threads[i], NULL, trial_division, &arr[i]);
    }

    for (int i = 0; i < length; i++) {
        int* factors;
        pthread_join(threads[i], (void**)&factors);

        printf("Factors of %d: ", arr[i]);
        for (int j = 0; factors[j] != 0; j++) {
            printf("%d ", factors[j]);
        }
        printf("\n");

        free(factors);
    }

    free(threads);
    return 0;
}

