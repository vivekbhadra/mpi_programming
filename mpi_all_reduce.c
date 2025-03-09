#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int size = 0;
    int rank = 0;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL) ^ (rank * 12345));

    int num = rand();
    int global_num = 0;

    /*
     * int MPI_Reduce(const void *sendbuf,   // Pointer to local data (input)
                      void *recvbuf,         // Pointer to result buffer (output, valid only in root process)
                      int count,             // Number of elements to be reduced
                      MPI_Datatype datatype, // Data type of elements (e.g., MPI_INT, MPI_DOUBLE)
                      MPI_Op op,             // Reduction operation (e.g., MPI_SUM, MPI_MIN, MPI_MAX)
                      int root,              // Rank of process that receives the final result
                      MPI_Comm comm)         // MPI communicator (usually MPI_COMM_WORLD)
     */


    MPI_Allreduce(&num, &global_num, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    printf("rank = %d: random number generated = %d\n", rank, num);

    printf("global_num = %d\n", global_num);

    MPI_Finalize();

    return 0;
}
