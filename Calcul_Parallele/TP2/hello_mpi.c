#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rang = -1, nbprocs = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nbprocs);

    printf("Hello from process %d of %d, running on CPU %d\n",
           rang, nbprocs, sched_getcpu());

    MPI_Finalize();
    return EXIT_SUCCESS;
}