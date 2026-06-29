OpenMP `target` Directive
=========================


The OpenMP ``target`` directive is a construct used to offload work from the CPU (host)
to an accelerator device such as a GPU. It allows a programmer to mark a region of code
that should be executed on a device instead of the host.

At a high level, ``target`` enables *device offloading*:

- CPU (host) launches a region

- GPU (device) executes it

- OpenMP runtime manages transfer and execution



**Exercise03: OpenMP Target**:

.. literalinclude:: ../../../exercises/3_target.c
   :language: c
   :linenos:


.. note::

   You can control OpenMP GPU execution using environment variables:

   - ``OMP_DEFAULT_DEVICE=1``: selects GPU/device 1 as the default target device.
   - ``OMP_TARGET_OFFLOAD=MANDATORY``: forces execution on a GPU, fails if no device is available.
   - ``OMP_TARGET_OFFLOAD=DEFAULT``: uses GPU if available, otherwise falls back to CPU.
   - ``OMP_TARGET_OFFLOAD=DISABLED``: disables GPU offloading, runs everything on CPU.


**Exercise04: OpenMP Target**:

.. literalinclude:: ../../../exercises/4_set_target.c
   :language: c
   :linenos:




When the compiler sees:

.. code-block:: c

    #pragma omp target

it performs the following steps:

1. Compiles the region for both CPU and GPU (if supported)
2. At runtime, launches the region on the target device
3. Transfers execution to the device
4. Executes the loop on the device
5. Returns control back to the host



.. note::

    The same idea in CUDA  is:

    .. code-block:: c

        __global__ void kernel()
        {
            for(int i = 0; i < 10; i++)
                printf("%d\n", i);
        }

        kernel<<<1,1>>>();





.. admonition:: Key Points
   :class: hint

    #. ``target`` enables device offloading in OpenMP
    #. It abstracts GPU execution behind a directive