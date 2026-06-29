
Distributing Compute
=======================

The directive:

.. code-block:: c

    #pragma omp target teams distribute parallel for reduction(+:inside)

combines multiple OpenMP execution layers to express **hierarchical parallelism on GPUs**. 


It breaks computation into:
- **Teams (device-level groups)**
- **Distribution (work partition across teams)**
- **Parallel execution (threads within teams)**
- **Loop-level parallelism**
- **Reduction (global aggregation across threads/teams)**



Hierarchical Execution Model
-----------------------------------

OpenMP maps this directive into a multiple levels of execution hierarchy:

**Teams**:

- The device launches multiple **teams**.

- Each team runs independently on the accelerator.

- Teams provide **coarse-grained parallelism**.

**Distribute**:

- The **loop iterations are divided among teams**.

- Each team receives a chunk of the iteration space.

- This is the first level of workload partitioning.

**Parallel**:

- Inside each team, iterations are further split among **threads**.

- Threads within a team execute concurrently.

- This provides **fine-grained parallelism**.

**For**:

- The `for` construct applies to loop iteration space.

- Ensures iterations are properly mapped across teams and threads.


**Exercise07: OpenMP Teams + Distribute + Parallel**:

.. literalinclude:: ../../../exercises/7_all_together.c
   :language: c
   :linenos:



.. admonition:: Key Points
   :class: hint

    #. The loop is split into chunks using **distribute**
    #. Chunks are assigned to **teams**
    #. Each team runs multiple **threads in parallel**
    #. Threads process loop iterations using **parallel for**

