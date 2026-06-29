#include <stdio.h>
#include <omp.h>

#define N 10

// Device-visible variables
#pragma omp declare target
float A[N], B[N];
#pragma omp end declare target

#pragma omp declare target
float square(float x) 
{
    return x * x;
}
#pragma omp end declare target

int main() 
{
    // Initialize host data
    for (int i = 0; i < N; i++) 
    {
        A[i] = i;
    }

    // Copy A to device, compute on device, copy B back
    #pragma omp target map(to: A[0:N]) map(from: B[0:N])
    {
        for (int i = 0; i < N; i++) {
            B[i] = square(A[i]);
        }
    }

    printf("%f\n", B[5]);
}
