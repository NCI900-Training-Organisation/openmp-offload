Low-level Memory Management 
================================



The core workflow in GPU offloading is:

1. Allocate memory on the GPU
2. Copy data from CPU to GPU
3. Execute computation on GPU
4. Copy results back to CPU
5. Free GPU memory

The difference between OpenMP approaches is *who manages these steps*.

High-Level Model (OpenMP Runtime Managed)
-----------------------------------------

In the high-level approach, OpenMP automatically manages device memory.

.. code-block:: c

    #pragma omp target enter data map(to: A[0:N], B[0:N])

    #pragma omp target teams distribute parallel for
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    #pragma omp target exit data map(delete: A[0:N], B[0:N], C[0:N])

Here:

- Memory allocation is handled by OpenMP
- Data transfer is handled using ``map`` and ``update``
- Device memory persists between kernels
- Memory is freed using ``exit data``

This approach is easier and safer.

Low-Level Model (Manual Device Control)
---------------------------------------

In the low-level approach, the programmer directly controls GPU memory.

**Exercise11: Persitant Data**:

.. literalinclude:: ../../../exercises/11_low_level.c
   :language: c
   :linenos:

Here:

- The programmer explicitly allocates GPU memory

- Data movement is manually controlled using ``omp_target_memcpy``

- The kernel directly uses device pointers

- Memory is explicitly freed

This approach is more complex but gives full control and better insight into performance.


+------------------------+---------------------------+
| High-level OpenMP      | Low-level OpenMP          |
+========================+===========================+
| Automatic memory mgmt  | Manual memory mgmt        |
+------------------------+---------------------------+
| Uses ``map`` clauses   | Uses ``omp_target_alloc``  |
+------------------------+---------------------------+
| Easier to write        | More control               |
+------------------------+---------------------------+
| Safer                  | Closer to CUDA style       |
+------------------------+---------------------------+

.. note::

    What happens if you remove `is_device_ptr`?

.. admonition:: Key Points
   :class: hint

    #. You can take full control of memory management using device pointers and manual allocation. 
    #. You are in charge of the full data life-cycle.