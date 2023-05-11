#include <stdio.h>
#include <mpi.h>

const int SIZE=10;
int main(void){

    int total_sum, local_sum, local_begin, local_end,
    local_n, comm_sz, my_rank;
    
    int vector[SIZE];


    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if(my_rank==0){
        for(int i=0;i<SIZE;i++){
            vector[i]=1+i;
        }
    }
    
    MPI_Bcast(vector,SIZE,MPI_INT,0,MPI_COMM_WORLD);

    local_n=SIZE/comm_sz;
    local_begin=local_n*my_rank;
    local_end=local_begin+local_n;

    local_sum=0;
    for(int i=local_begin;i<local_end;i++){
        local_sum+=vector[i];
    }

    MPI_Allreduce(&local_sum,&total_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

        
    int total_expected=0;
    for(int i=0;i<SIZE;i++){
        total_expected+=(i+1);
    }

    printf("I'm Process %d; Total expected: %d. Total given: %d\n",my_rank,total_expected,total_sum);

    MPI_Finalize();

}