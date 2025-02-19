#include <mpi.h>
#include <stdio.h>
#define N 12  /*Total vector size. Ensure N is divisible by 3 for 3 processes */

/*
 * This function is a dummy function which shows the computation each of the processor is doing locally.
 * for this exercise it doesn't matter what computation a processor it doing but important is to understand that it is
 * doing some processing or computation on the distributed data.
 **/
void Parallel_vector_sum(double local_x[], double local_y[], double local_z[], int local_n) 
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get process rank
    
    printf("Process %d is performing computation\n", rank);  

    for (int local_i = 0; local_i < local_n; local_i++) 
    {
        local_z[local_i] = local_x[local_i] + local_y[local_i];
    }
}

int main(int argc, char *argv[]) 
{
    int rank, size;
    double x[N], y[N], z[N]; /* x and y are initialised by the root process and then sent out to the other processes.
                              * Other processes do the computation they do and then send the result to the root process.
                              * At that point root process stores the result in z[].*/
    int local_n;             /* local_n is the size of the vector on each process, referred to as local_n */
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* MPI_COMM_WORLD is the default Communicator, rank is determined by the MPI
                                           * runtime automatically. */
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* the MPI runtime fetches the number of processes or the size from the
                                           * command line arguments we pass while running the program. */
    
    local_n = N / size;  /* the local_n is the size of the data smaller data set each process is allocated to. 
                          * Make sure the N is selected so that it is divisible by the size for better parallel allocation. */
    double local_x[local_n], local_y[local_n], local_z[local_n]; /* local_x, local_y are for the remote
                                                                  * processes to compute the values. These are used by
                                                                  * the remote process or the non-root processes.
                                                                  */
    
    /* Initialize vectors on root process*/
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            x[i] = i;                   /* here the root process is initialising the data set vectors x[] and y[] as we
                                         * do not have the real data set.
                                         */
            y[i] = i * 2; 
        }
    
        for(int i=0; i < N; i++)       /* this is just a print for debugging purposes.*/
        {
            printf("x[%d]=%lf ", i, x[i]);
            printf("\n");
            printf("y[%d]=%lf ", i, y[i]);
            printf("\n");
        }
    }

    // Scatter data to all processes
    MPI_Scatter(x,           /* the data to be processed*/
                local_n,     /* send count - how many elements in the data sent being sent to the non-root process*/
                MPI_DOUBLE,  /* MPI data type - type of the data being sent */
                local_x,     
                local_n, 
                MPI_DOUBLE, 
                0,           /* pass the rank of the root process, so that MPI knows where the whole data set is
                              * located. */
                MPI_COMM_WORLD);
    MPI_Scatter(y, 
                local_n, 
                MPI_DOUBLE, 
                local_y, 
                local_n, 
                MPI_DOUBLE, 
                0, 
                MPI_COMM_WORLD); /* same as in the above case
                                  * while scattering the vector x*/
    
    // Local computation using parallel vector sum function
    Parallel_vector_sum(local_x, local_y, local_z, local_n);
    
    // Gather results back to root process
    MPI_Gather(local_z, local_n, MPI_DOUBLE, z, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    // Root process prints final result
    if (rank == 0) {
        printf("Final vector z:\n");
        for (int i = 0; i < N; i++) {
            printf("x[%d] + y[%d] = z[%d]=%.1f\n", i, i, i, z[i]);
        }
        printf("\n");
    }
    
    MPI_Finalize();
    return 0;
}
