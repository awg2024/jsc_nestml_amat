#!/bin/bash
#SBATCH --job-name=nestml_benchmark
#SBATCH --account=jinm60
#SBATCH --partition=dc-cpu
#SBATCH --time=05:00:00
#SBATCH --nodes=8
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=64
#SBATCH --hint=nomultithread
#SBTACH --exclusive
#SBATCH --output=run_simulation_amat2_psc_exp_8_0_%j.out
#SBATCH --error=run_simulation_amat2_psc_exp_8_0_%j.err
#SBATCH --disable-perfparanoid

export OMP_PROC_BIND=TRUE
export PROGRAM="python3 Running/brunel_alpha_nest.py --simulated_neuron amat2_psc_exp --network_scale 20000.0 --nodes 8 --threads 128  --iteration 0 --benchmarkPath /p/project1/cslns/linssen1/jsc_nestml_amat/benchmark/Running/../Output_MPI/timings_strong_scaling_mpi --rng_seed 601453227"
srun $PROGRAM