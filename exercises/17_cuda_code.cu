#include <stdio.h>
#include <stdint.h>
#include <cuda.h>

#define N 100000000ULL

__device__ uint32_t hash_seed(uint32_t seed) {
    seed = (seed ^ 61) ^ (seed >> 16);
    seed *= 9;
    seed = seed ^ (seed >> 4);
    seed *= 0x27d4eb2d;
    seed = seed ^ (seed >> 15);
    return seed;
}

__device__ uint32_t xorshift32(uint32_t *state)
{
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

__device__ float random_float(uint32_t *state)
{
    return xorshift32(state) * (1.0f / 4294967295.0f); 
}

__global__ void monte_carlo_pi(unsigned long long total_samples, unsigned long long *global_inside)
{
    __shared__ unsigned long long s_inside[256];

    int tid = threadIdx.x;
    long long global_id = blockIdx.x * blockDim.x + threadIdx.x;
    long long stride = blockDim.x * gridDim.x;

    uint32_t seed = hash_seed((uint32_t)global_id + 1);
    unsigned long long local_count = 0;

    for (long long i = global_id; i < total_samples; i += stride)
    {
        float x = random_float(&seed);
        float y = random_float(&seed);

        if (x * x + y * y <= 1.0f)
        {
            local_count++;
        }
    }

    s_inside[tid] = local_count;
    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s >>= 1)
    {
        if (tid < s)
        {
            s_inside[tid] += s_inside[tid + s];
        }
        __syncthreads();
    }

    if (tid == 0)
    {
        atomicAdd(global_inside, s_inside[0]);
    }
}

int main()
{
    unsigned long long h_inside = 0;
    unsigned long long *d_inside;

    cudaMalloc(&d_inside, sizeof(unsigned long long));
    cudaMemcpy(d_inside, &h_inside, sizeof(unsigned long long), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = 512; 

    // --- CUDA Event Configuration ---
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Record the start event
    cudaEventRecord(start);

    // Launch Kernel
    monte_carlo_pi<<<blocks, threads>>>(N, d_inside);

    // Record the stop event
    cudaEventRecord(stop);

    // Wait for the stop event to complete on the GPU
    cudaEventSynchronize(stop);

    // Calculate the elapsed time
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    // --------------------------------

    cudaMemcpy(&h_inside, d_inside, sizeof(unsigned long long), cudaMemcpyDeviceToHost);

    double pi = 4.0 * (double)h_inside / (double)N;

    printf("Pi = %.10f\n", pi);
    printf("Kernel Execution Time: %.4f ms\n", milliseconds);

    // Clean up events
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_inside);
    
    return 0;
}