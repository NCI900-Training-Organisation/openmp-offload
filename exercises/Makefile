# =========================
# NVIDIA HPC SDK + CUDA Makefile
# =========================

CC      = nvc
CFLAGS  = -mp=gpu

NVCC    = nvcc
NVCCFLAGS = -O3

# -------------------------
# OpenMP sources
# -------------------------
OMP_SRCS = 1_pi_serial.c 2_pi_omp.c 3_target.c 4_set_target.c \
           5_parallel.c 6_team.c 7_all_together.c 8_static_arrays.c \
           9_dynamic_arrays.c 10_alloc_delete.c 11_low_level.c \
           12_declare_fail.c 13_declare.c 14_team_optimise.c \
           16_simd.c

OMP_EXECS = $(OMP_SRCS:.c=)

# -------------------------
# CUDA sources
# -------------------------
CUDA_SRCS = 17_cuda_code.cu 18_cuda_optimised.cu
CUDA_EXECS = $(CUDA_SRCS:.cu=)

# -------------------------
# RULE 1: make all
# -------------------------
all: openmp cuda

# -------------------------
# RULE 2: OpenMP build
# -------------------------
openmp: $(OMP_EXECS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

# -------------------------
# RULE 3: CUDA build
# -------------------------
cuda: $(CUDA_EXECS)

%: %.cu
	$(NVCC) $(NVCCFLAGS) $< -o $@

# -------------------------
# clean
# -------------------------
clean:
	rm -f $(OMP_EXECS) $(CUDA_EXECS)

.PHONY: all openmp cuda clean