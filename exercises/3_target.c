#include <stdio.h>
#include <omp.h>

int main(void)
{
    printf("Host: initial device %d\n", omp_get_initial_device());
    printf("Total devices: %d\n", omp_get_num_devices());
    printf("Default device: %d\n", omp_get_default_device());

    #pragma omp target
    {
        printf("Inside target region\n");
        printf("Device num (inside target): %d\n", omp_get_device_num());

        for (int i = 0; i < 10; i++)
        {
            printf("%d\n", i);
        }
    }

    return 0;
}