Value of Pi
====================


The Monte Carlo method estimates the value of :math:`\pi` by generating
a large number of random points inside a square and counting how many fall
inside a quarter circle.

The method relies on probability. If the random points are uniformly
distributed, then the fraction of points that lie inside the quarter
circle is approximately equal to the fraction of the square's area
occupied by the quarter circle.

Mathematical Background
-----------------------

Consider a unit square with a quarter circle of radius 1.

.. math::

   \text{Area of square} = 1

.. math::

   \text{Area of quarter circle} = \frac{\pi}{4}

Therefore,

.. math::

   \frac{\text{Points inside}}{\text{Total points}}
   \approx
   \frac{\pi}{4}

Rearranging the equation gives the estimate for :math:`\pi`:

.. math::

   \pi \approx 4 \times
   \frac{\text{Points inside}}
        {\text{Total points}}

Algorithm
---------

The algorithm follows these steps:

1. Generate a large number of random points within the unit square.
2. For each point, determine whether it lies inside the quarter circle.
3. Count the number of points that fall inside the quarter circle.
4. Estimate :math:`\pi` using the ratio of points inside the quarter circle
   to the total number of points generated.

.. note::

    Increasing the number of random points generally improves the accuracy
    of the estimate, although it also increases the execution time.

Why This Example?
-----------------

The Monte Carlo method is an excellent example for learning parallel
programming because each random point can be generated and tested
independently of every other point. There are no dependencies between
iterations, making the computation an *embarrassingly parallel* problem.

This means the work can be divided among multiple CPU threads or GPU
threads with very little communication or synchronisation, allowing the
program to scale efficiently as more processing resources are added.

.. exercise:: Exercise00: Calculate the value of :math:`\pi` using the Monte Carlo method

   .. literalinclude:: ../../../exercises/1_pi_serial.c
      :language: c
      :linenos:

.. exercise:: Exercise01: CPU parallelisation

   .. literalinclude:: ../../../exercises/2_pi_omp.c
      :language: c
      :linenos:


.. note:: 

    `omp_get_wtime()` is an OpenMP utility function used to measure wall-clock (real) time.



.. admonition:: Key Points
   :class: hint

    #. Random points are sampled in a unit square; the inside/outside ratio converges to :math:`\pi` as samples increase.
    #. Each iteration is independent, so work can be split across threads with minimal or no synchronisation, making it ideal for parallelisation.