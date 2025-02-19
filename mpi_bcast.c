#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int world_rank, world_size;
    int root_rank; // This will store the rank of the root process

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Root process sets its rank
    if (world_rank == 0) {
        root_rank = world_rank;
        printf("Root process (Rank %d) is broadcasting its rank...\n", root_rank);
    }

    // Broadcasting the root process rank to all processes
    MPI_Bcast(&root_rank, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process prints the received root rank
    printf("Process %d received root rank: %d\n", world_rank, root_rank);

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
