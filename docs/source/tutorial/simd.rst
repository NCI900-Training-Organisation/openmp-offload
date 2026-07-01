SIMD in OpenMP
==============

Overview
--------

``simd`` is an OpenMP directive that instructs the compiler to vectorise a loop.
Instead of processing one loop iteration at a time, multiple iterations are
executed simultaneously using SIMD (Single Instruction, Multiple Data)
instructions.

SIMD is designed for loops where each iteration is independent of the others.


.. note::

   In most cases, adding ``simd`` will not improve performance because modern
   compilers often vectorise such loops automatically.

   GPUs it is mostly redundant because the hardware already provides large-scale data parallelism 
   through SIMT execution.






``simd`` is most effective when:

* Each loop iteration is independent.
* The same operation is performed on many data elements.
* Memory accesses are regular and contiguous.
* There are no loop-carried dependencies.


**Exercise16: SIMD **:

.. literalinclude:: ../../../exercises/16_simd.c
   :language: c
   :linenos:


.. admonition:: Key Points
   :class: hint

    #. The ``simd`` directive enables instruction-level parallelism.
    #. May not be very useful with GPUs.