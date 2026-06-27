#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const long N = 100000000;

    long inside = 0;

    for (long i = 0; i < N; i++) {

        unsigned int seed = (unsigned int)i;

        float x =
            (float)rand_r(&seed) /
            (float)RAND_MAX;

        float y =
            (float)rand_r(&seed) /
            (float)RAND_MAX;

        if (x * x + y * y <= 1.0f) {
            inside++;
        }
    }

    double pi =
        4.0 * (double)inside /
        (double)N;

    printf("Points: %ld\n", N);
    printf("Inside: %ld\n", inside);
    printf("Pi ≈ %.10f\n", pi);

    return 0;
}