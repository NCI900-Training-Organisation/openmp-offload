Data Mapping
============

When a program is offloaded to an accelerator such as a GPU, the host (CPU)
and device (GPU) have separate memory spaces. Before a GPU can access data,
it must first exist in the device's memory.

The ``target`` directive creates a region of code that executes on the device,
while the ``map`` clause tells OpenMP which data should be transferred between
the host and the device.

How Data Mapping Works
----------------------

When OpenMP encounters a ``target`` region with a ``map`` clause, the runtime
automatically performs the following steps:

1. Allocate memory on the device.
2. Copy input data from the host to the device (if required).
3. Execute the target region on the device.
4. Copy results back to the host (if required).
5. Free the temporary device memory when the target region finishes.

For example,

.. code-block:: c

    #pragma omp target map(to: A, B) map(from: C)
    {
        ...
    }

is conceptually equivalent to

.. code-block:: text

    Allocate device memory for A
    Allocate device memory for B
    Allocate device memory for C

    Copy A to device
    Copy B to device

    Execute code on GPU

    Copy C back to host

    Free device memory

The programmer does **not** explicitly allocate GPU memory when using the
``map`` clause. The OpenMP runtime performs all memory allocation and data
transfers automatically.

Mapping Static Arrays
---------------------

Consider the following example:

**Exercise08: Static arrays**:

.. literalinclude:: ../../../exercises/8_static_arrays.c
   :language: c
   :linenos:

Here, ``A``, ``B`` and ``C`` are statically allocated arrays whose sizes are
known at compile time.

Since the compiler already knows the size of each array, simply specifying the
array name is sufficient.

- ``map(to: A, B)`` copies ``A`` and ``B`` from the host to the device before execution.

- ``map(from: C)`` copies ``C`` back to the host after execution.

OpenMP automatically allocates enough memory on the GPU for each array.

Mapping Dynamically Allocated Arrays
------------------------------------

Now consider dynamically allocated arrays:

**Exercise09: Dynamic arrays**:

.. literalinclude:: ../../../exercises/9_dynamic_arrays.c
   :language: c
   :linenos:

Unlike static arrays, a pointer only stores a memory address.

OpenMP cannot determine how much memory should be copied simply from the
pointer value.

Instead, an **array section** must be specified.

.. code-block:: c

    A[0:N]

This means

- start at element ``0``

- copy ``N`` elements

OpenMP uses this information to

- allocate space for ``N`` elements on the GPU

- copy those elements to the device

- execute the kernel

- copy the results back.

Common Mapping Types
--------------------

OpenMP provides several mapping types depending on how data should be moved.

``to``
~~~~~~

Copy data **from the host to the device** before execution.

Useful for input data that is read by the GPU.

.. code-block:: c

    #pragma omp target map(to: A)

``from``
~~~~~~~~

Copy data **from the device back to the host** after execution.

Useful for output data produced by the GPU.

.. code-block:: c

    #pragma omp target map(from: C)

``tofrom``
~~~~~~~~~~

Copy data to the device before execution **and** back to the host afterwards.

Useful when the device both reads and modifies the data.

.. code-block:: c

    #pragma omp target map(tofrom: A)



.. admonition:: Key Points
   :class: hint


    #. The ``map`` clause tells OpenMP which data should be transferred.
    #. OpenMP automatically allocates and frees device memory for mapped variables.
    #. Static arrays can be mapped by name because their size is known at compile time.
    #. Dynamically allocated arrays require array sections (e.g. ``A[0:N]``) so OpenMP knows how much memory to allocate and transfer.
    #. ``to``, ``from`` and ``tofrom`` are the most commonly used mapping types for transferring data between the host and device.