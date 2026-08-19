#!/bin/bash
# this script is building nest to be used on a local machine or to be used on a single node 
ml Stages/2024 GCC Boost ParaStationMPI GSL jemalloc Python SciPy-Stack mpi4py CMake Autotools

echo installing nestml-simulator

#Install nestsimulator
rm -rf nest-build
rm -rf nest-simulator-install # cleaning out previous versions 


# Paths
srcPath=$(pwd)/nest-simulator
installPath=$(pwd)/nest-simulator-install # current dir / nest sim 

mkdir nest-build
mkdir nest-simulator-install

cd nest-build

cmake -DCMAKE_INSTALL_PREFIX:PATH=$installPath $srcPath -Dwith-mpi=OFF -Dwith-optimize="-O3" -Dwith-readline=OFF -Dwith-detailed-timers=ON # cmake mpi off, optimise flag -03 default 
make -j24 install # 24 nodes together to install 

cd ..

echo installing nestml
#install nestml
cd nestml
python3 -m pip install .
cd ..

source nest-simulator-install/bin/nest_vars.sh  # reads and loads variables into an active environment via source 

echo installing custom neurons
#install custom neurons

source updateCustomNeurons.sh # reads and loads custom neurons based on user spec 

source run.sh
