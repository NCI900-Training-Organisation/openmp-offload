#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main(void)
{
    int *A = (int *)malloc(N * sizeof(int));
    int *B = (int *)malloc((N+1) * sizeof(int));
    int *C = (int *)malloc(N * sizeof(int));

    if (!A || !B || !C) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize input arrays
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = 2 * i;
        C[i] = 0;
    }
    B[N] = 2 * N;

    // Offload computation to the GPU
    #pragma omp target map(to: A[0:N], B[1:N]) map(from: C[0:N])
    {
        for (int i = 0; i < N; i++) {
            C[i] = A[i] + B[i + 1]; // OpenMP preserves host indexes.
        }
    }

    printf("C[0] = %d\n", C[0]);
    printf("C[N-1] = %d\n", C[N-1]);

    free(A);
    free(B);
    free(C);

    return 0;
}
