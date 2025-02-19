#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROOT 0

int main(int argc, char** argv) {
    int world_rank, world_size;
    int *send_data = NULL;
    int recv_data;
    int gathered_data[4]; // Assume 4 processes for simplicity

    // Initialize MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Root process initializes the send buffer
    if (world_rank == ROOT) {
        send_data = (int*)malloc(world_size * sizeof(int));
        for (int i = 0; i < world_size; i++) {
            send_data[i] = (i + 1) * 10; // Example data
        }
        printf("Root process distributing data: ");
        for (int i = 0; i < world_size; i++) {
            printf("%d ", send_data[i]);
        }
        printf("\n");
    }

    // Scatter data from root to all processes
    MPI_Scatter(send_data, 1, MPI_INT, &recv_data, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
    printf("Process %d received value: %d\n", world_rank, recv_data);

    // Perform a computation: Square the received value
    recv_data *= recv_data;

    // Gather squared values back to the root process
    MPI_Gather(&recv_data, 1, MPI_INT, gathered_data, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    // Root process prints the gathered data
    if (world_rank == ROOT) {
        printf("Root process gathered squared values: ");
        for (int i = 0; i < world_size; i++) {
            printf("%d ", gathered_data[i]);
        }
        printf("\n");
        free(send_data); // Free allocated memory
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}

