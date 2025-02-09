#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, new_rank, new_size;
    MPI_Comm custom_comm;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    MPI_Init(&argc, &argv);
    
    // Get the rank and size in MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the hostname of the process
    MPI_Get_processor_name(hostname, &name_len);

    // Convert hostname into a unique integer for color
    int color = 0;
    for (int i = 0; i < name_len; i++) {
        color += hostname[i];  // Simple hash to convert hostname to an int
    }

    // Split communicators based on the host machine
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &custom_comm);

    // Get new rank and size in the split communicator
    MPI_Comm_rank(custom_comm, &new_rank);
    MPI_Comm_size(custom_comm, &new_size);

    printf("Global Rank: %d, New Rank: %d, New Size: %d, Host: %s\n",
           rank, new_rank, new_size, hostname);

    // Free the new communicator and finalize MPI
    MPI_Comm_free(&custom_comm);
    MPI_Finalize();
    
    return 0;
}

