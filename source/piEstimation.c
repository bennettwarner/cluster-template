
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char* argv[]) 
{

  int CirclePoints = 0;
  int i = 0;
  int TotalPoints = 0;
  int PointsInRegion = 0;
  int PointsRecv = 0;
  double piEstimate;
  double x_start, y_start;
  double x_rand, y_rand, rand_radius;
  double StartTime, StopTime, TotalTime;
  int MPI_rank, size, SquareWidth;
  double SquareDouble;
  MPI_Status status;

  TotalPoints = atoi(argv[1]);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &MPI_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  StartTime = MPI_Wtime();
  PointsInRegion = TotalPoints / size;
  srand( (unsigned)time(NULL) + MPI_rank );
  SquareWidth = (int) sqrt(size);
  SquareDouble = (int) sqrt(size);

  // Specify the points in the circle
  x_start = (double)(MPI_rank % SquareWidth) / SquareWidth;
  y_start = (double)((MPI_rank / SquareWidth)) / SquareWidth;

  printf("Rank %d of %d has started x %f and starting y %f on a square of size %d \n",
         MPI_rank, size, x_start, y_start, SquareWidth);

  for (i = 0; i < PointsInRegion; i++) 
  {
    x_rand = (double)rand() / ((double)RAND_MAX * SquareWidth) + x_start;
    y_rand = (double)rand() / ((double)RAND_MAX * SquareWidth) + y_start;
    rand_radius = (x_rand - (1/SquareDouble)) * (x_rand - (1/SquareDouble)) + (y_rand - (1/SquareDouble)) * (y_rand - (1/SquareDouble));
    if (rand_radius <= ((1/SquareDouble) * (1/SquareDouble))) 
	{
      CirclePoints += 1;
    }
  }

  StopTime = MPI_Wtime();
  TotalTime = StopTime - StartTime;
  
  MPI_Reduce(&CirclePoints, &PointsRecv, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (MPI_rank == 0) 
  {
    piEstimate = (double)(PointsRecv * size) / TotalPoints;
    if (size < 4) 
	{
        piEstimate = piEstimate * 2;
    }
    printf("the estimation of PI is: %f\n Process %d took: %lf \n", piEstimate, MPI_rank, TotalTime);
  }

  MPI_Finalize();
  return 0;
}
