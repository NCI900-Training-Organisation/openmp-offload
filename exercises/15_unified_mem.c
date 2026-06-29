#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    const int N = 1024;

    // Enable unified shared memory model
    #pragma omp requires unified_shared_memory

    // Host allocations only (no omp_target_alloc)
    float *A = (float *)malloc(N * sizeof(float));
    float *B = (float *)malloc(N * sizeof(float));
    float *C = (float *)malloc(N * sizeof(float));

    // Initialize host data
    for (int i = 0; i < N; i++) {
        A[i] = i * 1.0f;
        B[i] = 2.0f * i;
        C[i] = 0.0f;
    }

    // GPU computation (no explicit copies, no is_device_ptr)
    #pragma omp target
    {
        for (int i = 0; i < N; i++) {
            C[i] = A[i] + B[i];
        }
    }

    // Result is directly visible on host
    printf("C[0] = %f\n", C[0]);
    printf("C[N-1] = %f\n", C[N-1]);

    free(A);
    free(B);
    free(C);

    return 0;
}