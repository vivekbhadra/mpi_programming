#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int world_rank, world_size;
    double start_time, end_time;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Start execution timer
    start_time = MPI_Wtime();

    // Simulate some computation
    for (long i = 0; i < 100000000; i++);

    // Stop execution timer
    end_time = MPI_Wtime();

    // Print execution time for each process
    printf("Process %d completed execution in %f seconds\n", world_rank, end_time - start_time);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
