#!/bin/bash

# This bash script compiles the generated code in different target directories.
# Each directory contains a combination of neuron with or without a synapse model generated from NESTML.

source ../nest-simulator-install/bin/nest_vars.sh # load nest variables 

# this script repeats the exact 5 step loop for four differentiations of the MODEL 
# variations on what's being built. target_optimised, target std, target_plastic, target_plastic_noco variant (OLD VERSION). 

cd Running/targets_amat/target # DEFAULT NESTML AMAT loaded (might need to change) 
rm -rf CMakeCache.txt CMakeFiles
cmake .
make -j24 install
cd ../../..

cd Running/target_amat/target_cse
rm -rf CMakeCache.txt CMakeFiles
cmake .
make -j24 install
cd ../../..