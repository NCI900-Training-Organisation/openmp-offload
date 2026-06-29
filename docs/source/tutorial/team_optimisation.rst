Optimising Threads per Team i
=============================

In GPUs, performance is strongly influenced by how work is partitioned across:

- number of teams
- number of threads per team

The goal of tuning these parameters is to maximise device utilisation while
avoiding oversubscription and scheduling overhead.


Choosing the number of threads per team affects:

- **Occupancy**: how fully the GPU compute units are used

- **Load balancing**: how evenly loop iterations are distributed

- **Memory efficiency**: how well memory accesses are coalesced

- **Scheduling overhead**: too many small teams/threads increases overhead

If threads per team is too low:

- hardware resources are underutilised

- more teams are required, increasing scheduling overhead


If threads per team is too high:

- register and shared resource pressure increases

- occupancy may drop due to resource contention

Optimisation Strategy
---------------------
A good tuning strategy is typically:



1. Ensure enough total parallelism

   - total threads ≈ N / chunk size

2. Avoid extreme configurations

   - very small teams → high overhead

   - very large teams → low occupancy

3. Match hardware characteristics

   - GPU warp size and SM capacity indirectly influence ideal values

5. Experiment with combinations

   - performance is often workload-dependent


.. admonition:: Key Points
   :class: hint

    #. We can control the number of teams and thread per teams.
    #. Optimising threads per team is a balancing act between.