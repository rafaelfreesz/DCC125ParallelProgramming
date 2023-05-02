#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int SIZE=10;
int main(void){

   int local_n,comm_sz,my_rank;
   int* vector;
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


   MPI_Finalize();

}