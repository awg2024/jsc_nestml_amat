#!/bin/bash

# This bash script compiles the generated code in different target directories.
# Each directory contains a combination of neuron with or without a synapse model generated from NESTML.

source ../nest-simulator-install/bin/nest_vars.sh # load nest variables 

# this script repeats the exact step loop for four differentiations of the MODEL 

# DEFINITION ON THE FOLLOW NEURONAL MODELS 
# targets_amat = baseline testing (BASELINE)
# targets_amat_coeff = precompute coeffients (PATCH 1) 
# targets_amat_vm_tmp = replace only v_m_tmp (PATCH 2)
# target_amat_tmp = replace common coefficient alpha1, alpha2, v_m_tmp (PATCH 3) 



cd Running/targets_amat/target # DEFAULT NESTML AMAT compiled dir. Baseline 
rm -rf CMakeCache.txt CMakeFiles
cmake .
make -j24 install
cd ../../..

cd Running/target_amat_optimised_cse/target # Optimised CSE 
rm -rf CMakeCache.txt CMakeFiles
cmake .
make -j24 install
cd ../../..
