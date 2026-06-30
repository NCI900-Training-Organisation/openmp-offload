Unified Memory
===========================================


The directive ``#pragma omp requires unified_shared_memory`` enables
OpenMP Unified Shared Memory (USM) semantics for the program.

.. note::

   Although ``unified_shared_memory`` is part of the OpenMP 5.x specification,
   it may not be  supported by the NVIDIA HPC SDK.

It specifies that the program assumes a **single shared memory address space
between host and target devices**, allowing pointers to be directly used on
both without explicit data mapping.



When this directive is used:

- Host and device share a unified address space (logically or physically)
- Pointer values are valid on both host and device
- Explicit ``map`` clauses are generally not required for data movement
- Data transfer is handled implicitly by the runtime or hardware



**Exercise15: Unified Memory**:

.. literalinclude:: ../../../exercises/15_unified_mem.c
   :language: c
   :linenos:



This directive shifts OpenMP programming from an **explicit data-movement model**
(using ``map`` clauses) to a **shared-memory programming model**, making GPU
offloading behave more like standard multithreaded CPU programming.


.. admonition:: Key Points
   :class: hint
   

    #. Unified Shared Memory (USM) allows host and device to share a common memory address space.
    #. Reduces the need for explicit ``map`` clauses.
    #. It simplifies GPU programming by allowing the same pointers to be accessed on both the host and device.
   

