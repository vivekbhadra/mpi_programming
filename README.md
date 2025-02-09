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

Compiling custom communicator:  
mpicc -g -Wall -o mpi_custom_communicator mpi_custom_communicator.c  
mpiexec -n 4 ./mpi_custom_communicator
while true; do mpiexec --bind-to core --map-by core -n 4 ./mpi_custom_communicator; done   

