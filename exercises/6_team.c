#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp target teams parallel
    {
        int total_threads  = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int nteams  = omp_get_num_teams();

        int team_id = omp_get_team_num();

        if (thread_id == 0)
        {
            printf("Team %d of %d teams with threads %d \n", team_id, nteams, total_threads);
        }
    }

    return 0;
}
