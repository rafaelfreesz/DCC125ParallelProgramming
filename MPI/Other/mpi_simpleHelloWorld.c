#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(void){

    char msg[100];

    int comm_sz=0;
    int my_rank=0;


    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("Hello World! I'm process %d, and my_rank address is %p\n",my_rank, &my_rank);
    
    MPI_Finalize();

    return 0;
}