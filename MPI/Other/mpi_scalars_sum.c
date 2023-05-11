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

    if(my_rank!=0){
        MPI_Send(&local_sum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{
        total_sum=local_sum;

        printf("Process 0 returned sum (");
        for(int i=local_begin;i<local_end;i++){
            printf("%d+",i+1);
        }
        printf(") = %d\n",local_sum);
        
        for(int i=1;i<comm_sz;i++){
            MPI_Recv(&local_sum,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            total_sum+=local_sum;

            printf("Process %d returned sum (",i);
            for(int k=local_n*i;k<(local_n*i+local_n);k++){
                printf("%d+",k+1);
            }

            printf(") = %d\n",local_sum);
        }

        int total_expected=0;
        for(int i=0;i<n_scalars;i++){
            total_expected+=(i+1);
        }

        printf("\n\nTotal expected: %d. Total given: %d\n",total_expected,total_sum);

    }

    MPI_Finalize();

}