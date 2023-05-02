#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int SIZE=100;
int main(void){

   int local_n,comm_sz,my_rank;
   int* vector=NULL;
   int* vectorb=NULL;
   int* localVector;
   MPI_Comm comm;

   MPI_Init(NULL, NULL);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &comm_sz);
   MPI_Comm_rank(comm, &my_rank);

   local_n=SIZE/comm_sz;
   localVector=malloc(local_n*sizeof(int));

   if(my_rank==0){
        vector=malloc(SIZE*sizeof(int));

        for(int i=0;i<SIZE;i++){
            vector[i]=i+1;
        }

        MPI_Scatter(vector,local_n,MPI_INT,localVector,local_n,
        MPI_INT,0,comm);
        free(vector);
   }else{
        MPI_Scatter(vector,local_n,MPI_INT,localVector,local_n,
        MPI_INT,0,comm);    
   }

   printf("I'm process %d and that is my localVector:\n[",my_rank);

   for(int i=0;i<local_n-1;i++){
        printf("%d,",localVector[i]);
   }
        printf("%d]\n",localVector[local_n-1]);

    if(my_rank==0){
        vectorb=malloc(SIZE*sizeof(int));

        MPI_Gather(localVector,local_n,MPI_INT,vectorb,local_n,MPI_INT,0,comm);
    }else{
        MPI_Gather(localVector,local_n,MPI_INT,vectorb,local_n,MPI_INT,0,comm);
    }

    printf("I'm process %d and that is my result vector: ",my_rank);

    if(vectorb==NULL){
        printf("NULL\n");
    }else{
        printf("[");
        for(int i=0;i<SIZE-1;i++){
                printf("%d,",vectorb[i]);
        }
                printf("%d]\n",vectorb[SIZE-1]);
            
    }
    


   MPI_Finalize();

}