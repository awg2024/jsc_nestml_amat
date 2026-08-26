#!/bin/bash

# This bash script compiles the generated code in different target directories.
# Each directory contains a combination of neuron with or without a synapse model generated from NESTML.

source ../nest-simulator-install/bin/nest_vars.sh # load nest variables 

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
