#!/bin/bash

# JURECA environment for AMAT benchmark
module load Stages/2026
module load GCC/14.3.0
module load ParaStationMPI/5.13.0-1
module load CMake/3.31.8
module load nest-simulator/3.9

# Python environment containing benchmark dependencies
source /p/project1/paj2623/gray2/venvs/amat_hpc/bin/activate

# Work out paths relative to this script
RUNNING_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BENCHMARK_DIR="$(cd "${RUNNING_DIR}/.." && pwd)"

echo "-> RUNNING_DIR:   ${RUNNING_DIR}"
echo "-> BENCHMARK_DIR: ${BENCHMARK_DIR}"


# Make both NESTML extension modules visible to nest.Install()
export LD_LIBRARY_PATH="${RUNNING_DIR}/targets_amat/target:${RUNNING_DIR}/targets_amat_optimised_cse/target:${LD_LIBRARY_PATH:-}"

# debug info
# echo "-> LID_LIBRARY_PATH:   ${LD_LIBRARY_PATH}"

# Headless plotting for compute nodes
export MPLBACKEND=Agg

# Useful for Slurm logs
export PYTHONUNBUFFERED=1

# Always finish in /benchmark
cd "${BENCHMARK_DIR}"

echo "start.sh completed"
