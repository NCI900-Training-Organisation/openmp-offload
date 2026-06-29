#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
    const int N = 1024;
    const int device = omp_get_default_device();

    float *A_h = (float *)malloc(N * sizeof(float));
    float *B_h = (float *)malloc(N * sizeof(float));
    float *C_h = (float *)malloc(N * sizeof(float));

    // 1. Initialize host data
    for (int i = 0; i < N; i++) {
        A_h[i] = i * 1.0f;
        B_h[i] = 2.0f * i;
        C_h[i] = 0.0f;
    }

    // 2. Allocate device memory explicitly
    float *A_d = (float *)omp_target_alloc(N * sizeof(float), device);
    float *B_d = (float *)omp_target_alloc(N * sizeof(float), device);
    float *C_d = (float *)omp_target_alloc(N * sizeof(float), device);

    // 3. Copy data host to device
    omp_target_memcpy(A_d, A_h, N * sizeof(float), 0, 0,
                      device, omp_get_initial_device());

    omp_target_memcpy(B_d, B_h, N * sizeof(float), 0, 0,
                      device, omp_get_initial_device());

    // 4. GPU computation using device pointers
    #pragma omp target is_device_ptr(A_d, B_d, C_d)
    {
        for (int i = 0; i < N; i++) {
            C_d[i] = A_d[i] + B_d[i];
        }
    }

    // 5. Copy result device to host
    omp_target_memcpy(C_h, C_d, N * sizeof(float), 0, 0,
                      omp_get_initial_device(), device);

    // 6. Free device memory
    omp_target_free(A_d, device);
    omp_target_free(B_d, device);
    omp_target_free(C_d, device);

    // Verify result
    printf("C[0] = %f\n", C_h[0]);
    printf("C[N-1] = %f\n", C_h[N-1]);

    // Free host memory
    free(A_h);
    free(B_h);
    free(C_h);

    return 0;
}