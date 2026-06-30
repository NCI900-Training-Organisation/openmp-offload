#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp target parallel
    {

        int total_threads  = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int nteams  = omp_get_num_teams();

        if (0 == thread_id)
        {
            printf("Total thraeds = %d \n",total_threads);
            printf("Total teams = %d \n", nteams);
        }

        if (thread_id < 10)
        {
            printf("Thread %d of %d \n", thread_id, total_threads);
        }

    }

    return 0;
}
