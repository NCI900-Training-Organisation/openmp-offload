#include <stdio.h>
#include <stdint.h>
#include <omp.h>

#pragma omp declare target

// xorshift32 random number generator
static inline uint32_t xorshift32(uint32_t *state)
{
    uint32_t x = *state;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    *state = x;
    return x;
}

// Generate a float in [0,1)
static inline float random_float(uint32_t *state)
{
    return xorshift32(state) * (1.0f / 4294967296.0f);
}

#pragma omp end declare target

int main(void)
{
    const long N = 100000000;
    long inside = 0;

    double start = omp_get_wtime();

    printf("Default device: %d\n", omp_get_default_device());

    #pragma omp target device(0) map(tofrom: inside)
    for (long i = 0; i < N; i++)
    {
        // Each iteration gets a unique seed
        uint32_t seed = (uint32_t)(i + 1);

        float x = random_float(&seed);
        float y = random_float(&seed);

        if (x * x + y * y <= 1.0f)
            inside++;
    }

    double end = omp_get_wtime();

    double pi = 4.0 * (double)inside / (double)N;

    printf("Pi = %.10f\n", pi);
    printf("Execution Time = %.6f s\n", end - start);

    return 0;
}
