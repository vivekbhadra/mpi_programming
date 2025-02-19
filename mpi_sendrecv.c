#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) 
{
    int world_rank, world_size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int send_data = world_rank;
    int recv_data;

    MPI_Sendrecv(&send_data, 1, MPI_INT, (world_rank + 1) % world_size, 0,
                 &recv_data, 1, MPI_INT, (world_rank - 1 + world_size) % world_size, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received data %d from process %d\n", world_rank, recv_data, 
           (world_rank - 1 + world_size) % world_size);

    MPI_Finalize();
    return 0;
}
