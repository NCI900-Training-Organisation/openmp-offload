#include <stdio.h>
#include <omp.h>

#define N 1024

int main(void)
{
    static int A[N][N];
    static int B[N][N];
    static int C[N][N];

    // Initialize input arrays
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }

    // Offload computation to the GPU
    #pragma omp target map(to: A, B) map(from: C)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }

    printf("C[0][0] = %d\n", C[0][0]);
    printf("C[N-1][N-1] = %d\n", C[N-1][N-1]);

    return 0;
}