#!/bin/bash -l 
#SBATCH --job-name=amat_bench
#SBATCH --nodes=2 
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2
#SBATCH --output=slurm_output/slurm-amat-out_%j.txt
#SBATCH --error=slurm_error/slurm-amat-err_%j.txt
#SBATCH --time=00:10:00
#SBATCH --partition=dc-cpu
#SBATCH --account=paj2623

# clear all inherited login node 
module --force purge

# load system modules 
module load Stages/2026
module load GCC/14.3.0
module load ParaStationMPI/5.13.0-1
module load Python
module load nest-simulator/3.9
module load CMake

# activate your custom environment wrapper
source venvs/amat_hpc/bin/activate

# Point NEST directly to your compiled .so module paths
export NEST_MODULE_PATH="/p/project1/paj2623/gray2/target:$NEST_MODULE_PATH"
export LD_LIBRARY_PATH="/p/project1/paj2623/gray2/target:$LD_LIBRARY_PATH"

# excute python 
srun python amat_benchmarking.py static 2500