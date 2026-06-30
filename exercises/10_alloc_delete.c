#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
    const int N = 1024;

    float *A = malloc(N * sizeof(float));

    // Allocate memory on the device only.
    #pragma omp target enter data map(alloc: A[0:N])

    // Initialize the array entirely on the GPU.
    #pragma omp target teams distribute parallel for 
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }

    // Copy the results back.
    #pragma omp target update from(A[0:N])

    printf("A[10] = %.1f\n", A[10]);

    // Free device memory.
    #pragma omp target exit data map(delete: A[0:N])

    free(A);

    return 0;
}
