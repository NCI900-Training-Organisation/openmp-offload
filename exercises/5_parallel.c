#include <stdio.h>
#include <omp.h>

int main(void)
{
    #pragma omp target parallel
    {
        printf("Thread %d\n",
               omp_get_thread_num());
    }

    return 0;
}