#!/bin/bash
#SBATCH -t 1:00:00
#SBATCH -N 3
#SBATCH --ntasks-per-node 4

#echo command to stdout
set -x

# where do I start?
echo $SLURM_SUBMIT_DIR

module load mpi/gcc_openmpi

cd $scratch
mpicc pi_mc.c

for i in {2..12..2}
do
  echo "With ${i} processes"
  time mpirun -np $i ./a.out
done
