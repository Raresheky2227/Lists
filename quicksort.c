#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to check if the array is sorted
int isSorted(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Not sorted
        }
    }
    return 1; // Sorted
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <m> <n>\n", argv[0]);
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int size = 1 << n; // Calculate array size as 2^n
    int *arr = malloc(size * sizeof(int));

    if (!arr) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Seed the random number generator with current time
    srand(time(NULL));

    // Generate random integers in the range [0, m)
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % m;
    }

    // Sort the array using qsort function
    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare);
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f\n", elapsed);

    // Check if the array is sorted
    if (isSorted(arr, size)) {
        printf("Array is sorted.\n");
    } else {
        printf("Array is not sorted.\n");
    }

    free(arr);
    return 0;
}
