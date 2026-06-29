#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp target parallel
    {

        int total_threads  = omp_get_num_thread();

        int thread_id = omp_get_thread_num();

        printf("Thread %d of %d \n", thread_id, total_threads);

    }

    return 0;
}
