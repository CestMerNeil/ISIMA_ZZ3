#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rang, nbprocs;
    int dest, source;
    const int etiquette = 50;
    MPI_Status statut;
    char message[1000];
    char temp[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);
    MPI_Comm_size(MPI_COMM_WORLD, &nbprocs);

    source = (rang + nbprocs - 1) % nbprocs;
    dest = (rang + 1) % nbprocs;

    if (rang == 0)
    {
        sprintf(message, "P%d ", rang);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest, etiquette, MPI_COMM_WORLD);

        MPI_Recv(message, 1000, MPI_CHAR, source, etiquette, MPI_COMM_WORLD, &statut);
        printf("Bonjour de la part de %s\n", message);
    }
    else
    {
        MPI_Recv(message, 1000, MPI_CHAR, source, etiquette, MPI_COMM_WORLD, &statut);
        sprintf(temp, "P%d ", rang);
        strcat(message, temp);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest, etiquette, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}