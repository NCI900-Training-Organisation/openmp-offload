# =========================
# NVIDIA HPC SDK Makefile
# OpenMP GPU compilation
# =========================

# Load module (for reference, not executed inside make)
# module load nvidia-hpc-sdk/21.3

CC      = nvc
CFLAGS  = -mp=gpu

# List of all C sources
SRCS = 1_pi_serial.c 2_pi_omp.c 3_target.c 4_set_target.c \
       5_parallel.c 6_team.c 7_all_together.c 8_static_arrays.c \
       9_dynamic_arrays.c 10_alloc_delete.c 11_low_level.c \
       12_declare_fail.c 13_declare.c 14_team_optimise.c \
       16_simd.c 
       #15_unified_mem.c

# Generate executables by stripping .c
EXECS = $(SRCS:.c=)

# Default target
all: $(EXECS)

# Generic rule: compile each .c into same-named executable
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clean build artifacts
clean:
	rm -f $(EXECS)

# Optional: rebuild everything
rebuild: clean all

.PHONY: all clean rebuild