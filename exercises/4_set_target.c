#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    const long N = 100000000;
    long inside = 0;

    double start = omp_get_wtime();

    printf("Default device: %d\n", omp_get_default_device());

    #pragma omp target teams
    for (long i = 0; i < N; i++)
    {
        // Simple GPU-safe deterministic RNG (LCG-style hashing)
        unsigned int seed = (unsigned int)(i * 1664525u + 1013904223u);

        // Convert bits into [0,1]
        float x = (seed & 0xFFFF) / (float)0xFFFF;
        float y = ((seed >> 16) & 0xFFFF) / (float)0xFFFF;

        if (x * x + y * y <= 1.0f)
        {
            inside++;
        }
    }

    double end = omp_get_wtime();

    printf("Pi ~= %.10f\n",
           4.0 * (double)inside / (double)N);

    printf("Execution Time = %.6f s\n",
           end - start);

    return 0;
}
