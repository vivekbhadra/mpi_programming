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

    double min = ((double)rand() / RAND_MAX) * 50.0 + 1.0;  // Between 1 and 51
    double max = min + ((double)rand() / RAND_MAX) * 20.0;  // Ensures max > min
    double global_min = 0.0;
    double global_max = 0.0;

    /*
     * int MPI_Reduce(const void *sendbuf,   // Pointer to local data (input)
                      void *recvbuf,         // Pointer to result buffer (output, valid only in root process)
                      int count,             // Number of elements to be reduced
                      MPI_Datatype datatype, // Data type of elements (e.g., MPI_INT, MPI_DOUBLE)
                      MPI_Op op,             // Reduction operation (e.g., MPI_SUM, MPI_MIN, MPI_MAX)
                      int root,              // Rank of process that receives the final result
                      MPI_Comm comm)         // MPI communicator (usually MPI_COMM_WORLD)
     */


    MPI_Reduce(&min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    printf("rank = %d: min = %.2f max = %.2f\n", rank, min, max);

    if(rank == 0)
    {
        printf("global_min = %.2f\n", global_min);
        printf("global_max = %.2f\n", global_max);
    }

    MPI_Finalize();

    return 0;
}
