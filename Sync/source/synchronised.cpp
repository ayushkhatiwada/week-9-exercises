#include <mpi.h>

int main()
{
    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_ranks;
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    int neighbour_rank;


    if (rank == (n_ranks - 1)) {
        MPI_Recv(&neighbour_rank, 1, MPI_INT, (rank-1)%n_ranks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&rank, 1, MPI_INT, (rank+1)%n_ranks, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Ssend(&rank, 1, MPI_INT, (rank+1)%n_ranks, 0, MPI_COMM_WORLD);
        MPI_Recv(&neighbour_rank, 1, MPI_INT, (rank-1)%n_ranks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }



    printf("My rank is %d and the neighbour is rank %d\n", rank, neighbour_rank);

    MPI_Finalize();

    return 0;
}


/*
0 -> 1

1 -> 2

2 -> 3

3


if rank == n_ranks
    don't send





*/
