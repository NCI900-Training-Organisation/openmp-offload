#include <stdio.h>
#include <omp.h>

int main(void)
{
    printf("Default device: %d\n", omp_get_default_device());

    #pragma omp target device(1)
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