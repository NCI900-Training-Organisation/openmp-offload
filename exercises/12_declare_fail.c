#include <stdio.h>
#include <omp.h>

float square(float x) {
    return x * x;
}

int main() 
{
    const int N = 10;
    float A[N], B[N];

    for (int i = 0; i < N; i++) {
        A[i] = i;
    }

    #pragma omp target map(to: A[0:N]) map(from: B[0:N])
    {
        for (int i = 0; i < N; i++) {
            B[i] = square(A[i]);   // ❌ ERROR on many compilers
        }
    }

    printf("%f\n", B[5]);
}
