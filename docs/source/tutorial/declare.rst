Declare Target
=============

`declare target`  makes variables and functions available on the device, along with a `target` region 
to execute code on the GPU and `map` clauses to explicitly control data transfer between host and device.


``declare target`` for Variables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

    #pragma omp declare target
    float A[N], B[N];
    #pragma omp end declare target


- Creates GPU-visible versions of ``A`` and ``B``

- Allocates separate memory on the device

- Makes arrays accessible inside GPU execution regions

.. note::

    - Host and device still have **separate copies**

    - No automatic synchronization happens

    - CPU A ≠ GPU A until explicitly copied



``declare target`` for Functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

    #pragma omp declare target
    float square(float x) { return x * x; }
    #pragma omp end declare target



- Compiles ``square()`` for both CPU and GPU

- Allows the same function to run in either context

.. note::

    - Function becomes available on the device

    - It does not move data by itself


**Exercise13: Declare target**:

.. literalinclude:: ../../../exercises/13_declare.c
   :language: c
   :linenos:


.. admonition:: Key Points
   :class: hint


    #. ``declare target`` makes variables/functions available on GPU
    #. It does not transfer data automatically
    #. CPU and GPU memory are always separate

