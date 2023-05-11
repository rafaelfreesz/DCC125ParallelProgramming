#include <stdio.h>
#include <mpi.h>

int main(void){

    int n_scalars, total_sum, local_sum, local_begin, local_end,
    local_n, comm_sz, my_rank;
    
    n_scalars=100;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);


    local_n=n_scalars/comm_sz;
    local_begin=local_n*my_rank;
    local_end=local_begin+local_n;

    local_sum=0;
    for(int i=local_begin;i<local_end;i++){
        local_sum+=(i+1);
    }

    MPI_Allreduce(&local_sum,&total_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

        
    int total_expected=0;
    for(int i=0;i<n_scalars;i++){
        total_expected+=(i+1);
    }

    printf("I'm Process %d; Total expected: %d. Total given: %d\n",my_rank,total_expected,total_sum);

    MPI_Finalize();

}