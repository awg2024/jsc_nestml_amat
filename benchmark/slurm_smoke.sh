#!/bin/bash

#SBATCH --job-name=amat_smoke
#SBATCH --account=paj2623
#SBATCH --partition=dc-cpu-devel
#SBATCH --time=00:05:00

#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1
#SBATCH --hint=nomultithread

#SBATCH --output=amat_smoke_%j.out
#SBATCH --error=amat_smoke_%j.err


module load Stages/2026
module load GCC/14.3.0
module load ParaStationMPI/5.13.0-1
module load CMake/3.31.8
module load nest-simulator/3.9

source /p/project1/paj2623/gray2/venvs/amat_hpc/bin/activate


# sbatch starts in the directory from which it was submitted
cd "${SLURM_SUBMIT_DIR}"


export LD_LIBRARY_PATH="${SLURM_SUBMIT_DIR}/Running/targets_amat/target:${SLURM_SUBMIT_DIR}/Running/targets_amat_optimised_cse/target:${LD_LIBRARY_PATH:-}"

export MPLBACKEND=Agg
export PYTHONUNBUFFERED=1

export OMP_NUM_THREADS=${SLURM_CPUS_PER_TASK}
export SRUN_CPUS_PER_TASK=${SLURM_CPUS_PER_TASK}


echo "========================================"
echo "HOST: $(hostname)"
echo "SLURM_JOB_ID: ${SLURM_JOB_ID}"
echo "SLURM_NNODES: ${SLURM_NNODES}"
echo "SLURM_CPUS_PER_TASK: ${SLURM_CPUS_PER_TASK}"
echo "PWD: $(pwd)"
echo "========================================"


mkdir -p slurm_smoke_results


for MODEL in \
    amat2_psc_exp \
    amat_nestml \
    amat_nestml_cse

do

    echo
    echo "========================================"
    echo "TESTING ${MODEL}"
    echo "========================================"

    srun python3 Running/brunel_alpha_nest.py \
        --simulated_neuron "${MODEL}" \
        --network_scale 50 \
        --nodes 1 \
        --threads 1 \
        --iteration 0 \
        --rng_seed 12345 \
        --smoke_test \
        --simtime 999 \
        --benchmarkPath slurm_smoke_results

done


echo
echo "ALL SLURM SMOKE TESTS COMPLETED"
