#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // Required for offsetof macro

typedef struct {
    int id;       /* Unique identifier for the structure */
    double value; /* Floating point value associated with the structure */
} CustomStruct;

int main(int argc, char** argv) {
    int world_rank, world_size;
    MPI_Datatype custom_type;
    
    /* Initialize the MPI environment */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    /* Define block lengths, displacements, and data types */
    int block_lengths[2] = {1, 1}; /* Number of elements per block */
    MPI_Aint displacements[2];     /* Memory offsets for struct members */
    MPI_Datatype types[2] = {MPI_INT, MPI_DOUBLE}; /* Data types of struct members */

    /* Compute memory displacements */
    displacements[0] = offsetof(CustomStruct, id); /* Offset for 'id' field */
    displacements[1] = offsetof(CustomStruct, value); /* Offset for 'value' field */

    /* Create and commit the MPI custom datatype */
    MPI_Type_create_struct(2, block_lengths, displacements, types, &custom_type);
    MPI_Type_commit(&custom_type);

    /* Define and initialize data */
    CustomStruct data;
    if (world_rank == 0) {
        data.id = 42;
        data.value = 3.14;
        printf("Process %d sending: id = %d, value = %f\n", world_rank, data.id, data.value);
        
        /* Send the struct to process 1 */
        MPI_Send(&data, 1, custom_type, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        /* Receive the struct from process 0 */
        MPI_Recv(&data, 1, custom_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received: id = %d, value = %f\n", world_rank, data.id, data.value);
    }

    /* Free the custom datatype */
    MPI_Type_free(&custom_type);
    
    /* Finalize MPI */
    MPI_Finalize();

    return 0;
}
