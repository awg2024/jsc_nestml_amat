#!/bin/bash

# JURECA software stack
module load Stages/2026
module load GCC/14.3.0
module load ParaStationMPI/5.13.0-1
module load CMake/3.31.8
module load nest-simulator/3.9

# AMAT Python environment
source /p/project1/paj2623/gray2/venvs/amat_hpc/bin/activate

# Project location
export AMAT_HOME=/p/project1/paj2623/gray2
export PATH=/p/project1/paj2623/gray2/venvs/amat_hpc/bin:$PATH

cd "$AMAT_HOME"


