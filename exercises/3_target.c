#include <stdio.h>
#include <omp.h>

int main()
{
    printf("Host: initial device %d\n", omp_get_initial_device());
    printf("Total devices: %d\n", omp_get_num_devices());
    printf("Default device: %d\n", omp_get_default_device());

    #pragma omp target
    {
        printf("Device thread ID: %d\n", omp_get_thread_num());
        printf("Total device threads: %d\n", omp_get_num_threads());
    }

    return 0;
}
