
Teams
======

In OpenMP target regions, execution on accelerators (such as GPUs) is structured hierarchically using 
**teams**.

A *team* is a group of threads that executes cooperatively on a device. When a ``teams`` construct is 
used, OpenMP creates multiple such teams to distribute work across the device.


- A *team* is a coarse-grained unit of execution on the device.
- Multiple teams are launched simultaneously on the accelerator.
- Each team operates independently of others.
- Teams are analogous to CUDA thread blocks in GPU programming.
- Each team contains multiple threads.
- Threads within a team can cooperate and share data.

**Exercise05: OpenMP Target**:

.. literalinclude:: ../../../exercises/5_parallel.c
   :language: c
   :linenos:

.. note::

    1. How many threads are created?
    2. How many teams are launched?



**Exercise06: OpenMP Teams**:

.. literalinclude:: ../../../exercises/6_team.c
   :language: c
   :linenos:


.. note::

    How many teams are launched?


.. admonition:: Key Points
   :class: hint

   #. OpenMP teams are coarse-grained groups of threads launched on accelerators (e.g., GPUs) for device-level parallelism.
   #. Multiple teams run independently and in parallel, and each team contains multiple cooperating threads for shared execution.
