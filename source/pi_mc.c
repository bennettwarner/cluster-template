#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[]) {

  int nPointsInCircle  = 0;
  int i = 0;
  int nPointsTotal     = 0;
  int nPointsPerRegion = 0;
  int pointsReceived   = 0;
  double piEstimate;
  double x_start, y_start;
  double x_rand, y_rand, rand_radius;
  double start, stop, tpar;
  int rank, size, squareWidth;
  double sqWDub;
  MPI_Status status;

  nPointsTotal = atoi(argv[1]);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Seed RNG and make calculations for constants
  start = MPI_Wtime();
  nPointsPerRegion = nPointsTotal / size;
  srand( (unsigned)time(NULL) + rank ); // seed differently per node
  squareWidth = (int) sqrt(size);
  sqWDub = (int) sqrt(size);
  // Place and record points in the circle
  x_start = (double)(rank % squareWidth) / squareWidth;
  y_start = (double)((rank / squareWidth)) / squareWidth;

  //printf("Rank %d out of %d has starting x %f and starting y %f on a square of size %d \n",
 //       rank, size, x_start, y_start, squareWidth);

  for (i = 0; i < nPointsPerRegion; i++) {
    x_rand = (double)rand() / ((double)RAND_MAX * squareWidth) + x_start;
    y_rand = (double)rand() / ((double)RAND_MAX * squareWidth) + y_start;
    rand_radius = (x_rand - (1/sqWDub)) * (x_rand - (1/sqWDub)) + (y_rand - (1/sqWDub)) * (y_rand - (1/sqWDub));
    if (rand_radius <= ((1/sqWDub) * (1/sqWDub))) {
      nPointsInCircle += 1;
    }
  }
  stop = MPI_Wtime();
  tpar = stop - start;
  
  MPI_Reduce(&nPointsInCircle, &pointsReceived, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    piEstimate = (double)(pointsReceived * size) / nPointsTotal;
    if (size < 4) {
        piEstimate = piEstimate * 2;
    }
    printf("the estimation of PI is: %f\n Process %d took: %lf \n", piEstimate, rank, tpar);
  }

  MPI_Finalize();
  return 0;
}
