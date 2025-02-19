Installing MPI:
sudo apt update  
sudo apt install openmpi-bin openmpi-common openmpi-doc libopenmpi-dev   

mpicc --version  
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0  
Copyright (C) 2021 Free Software Foundation, Inc.  
This is free software; see the source for copying conditions.  
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

Compiling the MPI Program:  
mpicc -g -Wall -o mpi_hello mpi_hello.c  

#Running the MPI Program
mpiexec -n 1 ./mpi_hello  
Greetings from process 0 of 1!  
mpiexec -n 4 ./mpi_hello  
Greetings from process 0 of 4!  
Greetings from process 1 of 4!  
Greetings from process 2 of 4!  
Greetings from process 3 of 4!  

Compiling mpi_vector_addition.c:
mpicc -o mpi_vector_addition mpi_vector_addition.c

Running mpi_vector_addition.c on Ubuntu:
mpirun -np 3 ./mpi_vector_addition 
x[0]=0.000000 
y[0]=0.000000 
x[1]=1.000000 
y[1]=2.000000 
x[2]=2.000000 
y[2]=4.000000 
x[3]=3.000000 
y[3]=6.000000 
x[4]=4.000000 
y[4]=8.000000 
x[5]=5.000000 
y[5]=10.000000 
x[6]=6.000000 
y[6]=12.000000 
x[7]=7.000000 
y[7]=14.000000 
x[8]=8.000000 
y[8]=16.000000 
x[9]=9.000000 
y[9]=18.000000 
x[10]=10.000000 
y[10]=20.000000 
x[11]=11.000000 
y[11]=22.000000 
Final vector z:
x[0] + y[0] = z[0]=0.0
x[1] + y[1] = z[1]=3.0
x[2] + y[2] = z[2]=6.0
x[3] + y[3] = z[3]=9.0
x[4] + y[4] = z[4]=12.0
x[5] + y[5] = z[5]=15.0
x[6] + y[6] = z[6]=18.0
x[7] + y[7] = z[7]=21.0
x[8] + y[8] = z[8]=24.0
x[9] + y[9] = z[9]=27.0
x[10] + y[10] = z[10]=30.0
x[11] + y[11] = z[11]=33.0

