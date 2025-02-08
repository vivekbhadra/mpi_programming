#include <stdio.h>
#include <string.h>   /* For strlen */
#include <mpi.h>      /* For MPI functions, etc */

const int MAX_STRING = 100;

int main(void) {
    char greeting[MAX_STRING];
    int comm_sz;  /* Number of processes */
    int my_rank;  /* My process rank */

    /* Initialize the MPI environment */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);  /* Get number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);  /* Get process rank */

    if (my_rank != 0) {
        /* Non-zero processes send a greeting message to process 0 */
        sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        /* Process 0 prints its own greeting */
        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);

        /* Process 0 receives messages from all other processes */
        for (int q = 1; q < comm_sz; q++) {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }

    /* Finalize the MPI environment */
    MPI_Finalize();
    return 0;
} /* main */

