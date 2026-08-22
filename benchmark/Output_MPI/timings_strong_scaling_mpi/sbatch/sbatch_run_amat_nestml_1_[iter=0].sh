#!/bin/bash

#SBATCH --job-name=nestml_amat_benchmark
#SBATCH --account=paj2623 
#SBATCH --partition=dc-cpu
#SBATCH --time=00:10:00

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --hint=nomultithread

#SBATCH --output=run_simulation_amat_nestml_1_0_%j.out
#SBATCH --error=run_simulation_amat_nestml_1_0_%j.err

module load Stages/2026
module load GCC/14.3.0
module load ParaStationMPI/5.13.0-1
module load CMake/3.31.8
module load nest-simulator/3.9

source /p/project1/paj2623/gray2/venvs/amat_hpc/bin/activate

export LD_LIBRARY_PATH="${PWD}/Running/targets_amat/target:${PWD}/Running/targets_amat_optimised_cse/target:${LD_LIBRARY_PATH:-}"

export MPLBACKEND=Agg
export PYTHONUNBUFFERED=1
export OMP_PROC_BIND=TRUE

export SRUN_CPUS_PER_TASK=${SLURM_CPUS_PER_TASK}

export PROGRAM="python3 Running/brunel_alpha_nest.py \
--simulated_neuron amat_nestml \
--network_scale 2500 \
--nodes 1 \
--threads 1 \
--iteration 0 \
--benchmarkPath /p/project1/paj2623/gray2/benchmark/Running/../Output_MPI/timings_strong_scaling_mpi \
--rng_seed 959920514 \
--smoke_test \
--simtime 100"



srun $PROGRAM