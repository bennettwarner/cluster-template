#!/bin/bash
#SBATCH -p RM
#SBATCH -t 1:00:00
#SBATCH -N 2
#SBATCH --ntasks-per-node 28

#echo command to stdout
set -x

# where do I start?
echo $SLURM_SUBMIT_DIR

module load mpi/gcc_openmpi

#Assuming hello.c is in $scratch
cd $scratch
mpicc hello.c

for i in {2..28..2}
do
  echo "With ${i} processes"
  time mpirun -np $i ./a.out
done
