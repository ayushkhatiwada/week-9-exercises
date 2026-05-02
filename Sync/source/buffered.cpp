#include <mpi.h>

int main()
{
    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_ranks;
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
    int neighbour_rank;

    // replace this call with a MPI_Bsend
    // MPI_Send(&rank, 1, MPI_INT, (rank+1)%n_ranks, 0, MPI_COMM_WORLD);


    // work out buffer size
    // size_of_message + fixed overhead of size MPI_BSEND_OVERHEAD per message
    const int buffer_size = sizeof(int) + MPI_BSEND_OVERHEAD;

    // create buffer
    char* buffer = new char[buffer_size];

    // Attach a user-provided buffer for sending
    // MPI_Buffer_attach is a C-style API, it expects a raw pointer
    MPI_Buffer_attach(buffer, buffer_size);

    MPI_Bsend(&rank, 1, MPI_INT, (rank+1)%n_ranks, 0, MPI_COMM_WORLD);



    MPI_Recv(&neighbour_rank, 1, MPI_INT, (rank-1)%n_ranks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("My rank is %d and the neighbour is rank %d\n", rank, neighbour_rank);



    // After the communication but before the MPI_Finalize we need to detach the buffer
    void* detached_buffer;
    int detached_size;
    MPI_Buffer_detach(&detached_buffer, &detached_size);

    delete[] buffer;

    MPI_Finalize();

    return 0;
}
