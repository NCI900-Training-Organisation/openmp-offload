Persistent Data Management
==========================

The ``target`` directive automatically allocates device memory, transfers data,
executes the target region, and then frees the device memory when execution
completes.

This is convenient for a single offload region, but it can become inefficient
when multiple GPU kernels operate on the same data. In that case, the data is
copied to and from the device every time a ``target`` region is entered.

OpenMP provides three directives for managing device data explicitly:

- ``target enter data`` - Allocate and optionally initialize device data.
- ``target update`` - Synchronize data between the host and device.
- ``target exit data`` - Remove data from the device.

Using these directives allows data to remain on the GPU across multiple kernel
launches, avoiding unnecessary memory transfers.

target enter data
-----------------

The ``target enter data`` directive creates a persistent copy of data on the
device before any kernels are launched.

.. code-block:: c

    #pragma omp target enter data map(to: A[0:N], B[0:N])

This directive performs the following operations:

1. Allocate memory for ``A`` and ``B`` on the device.
2. Copy the contents of ``A`` and ``B`` from the host to the device.
3. Leave the data allocated on the device for future use.

Unlike a ``target`` region, the device memory is **not** automatically released
when this directive completes.

A common use case is copying input data to the GPU once before executing
multiple kernels.

target update
-------------

The ``target update`` directive synchronizes data between the host and the
device.

It **does not** allocate or free device memory—it simply copies data between
existing host and device allocations.

Updating the device
~~~~~~~~~~~~~~~~~~~

To copy data from the host to the device:

.. code-block:: c

    #pragma omp target update to(A[0:N])

This is useful when the CPU has modified ``A`` and the GPU requires the updated
values before executing another kernel.

Updating the host
~~~~~~~~~~~~~~~~~

To copy data from the device back to the host:

.. code-block:: c

    #pragma omp target update from(C[0:N])

This is useful when the GPU has modified ``C`` and the CPU needs to access the
updated results without deleting the device copy.

target exit data
----------------

The ``target exit data`` directive removes persistent data from the device.

Delete device data
~~~~~~~~~~~~~~~~~~

To remove the device copy without copying data back:

.. code-block:: c

    #pragma omp target exit data map(delete: A[0:N])

This releases the device memory associated with ``A``.

Copy back and remove
~~~~~~~~~~~~~~~~~~~~

To copy data back to the host before removing it from the device:

.. code-block:: c

    #pragma omp target exit data map(from: C[0:N])

This performs two operations:

1. Copy ``C`` from the device to the host.
2. Free the device memory associated with ``C``.

Example Workflow
----------------

The following example demonstrates a typical workflow for persistent device data.

**Exercise10: Persitant Data**:

.. literalinclude:: ../../../exercises/10_alloc_delete.c
   :language: c
   :linenos:



.. note::

    If you do not use `target enter data`, `target update`, or `target exit data`, OpenMP uses the default
    `target` behavior where each target region is treated independently. This means that for every 
    `target` region, the runtime allocates fresh device memory, copies the required input data to 
    the device according to the `map` clauses, executes the kernel on the accelerator, copies the 
    results back to the host if needed, and then frees the device memory once the region completes.

.. admonition:: Key Points
   :class: hint

    #. ``target enter data``- Allocate and optionally initialize persistent device data.
    #. ``target update``- Synchronize existing data between the host and device.
    #. ``target exit data``- Copy back (optional) and remove persistent device data.
