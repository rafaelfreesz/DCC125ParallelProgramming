#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */


int main(void) {
   int comm_sz, my_rank;
   int global_vector[2];              
   int local_vector[2];              

   MPI_Init(NULL, NULL);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   
   local_vector[0]=1;
   local_vector[1]=2;


printf("I'm process %d. My loca_vector is [%d,%d]\n",my_rank,local_vector[0], local_vector[1]);

   
   MPI_Reduce(local_vector,global_vector,2,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
   
   if(my_rank==0){
  printf("Expected global_vector: [%d,%d]\n\n",comm_sz*1,comm_sz*2);
  printf("Given global_vector: [%d,%d]\n\n",global_vector[0],global_vector[1]);
   }


   MPI_Finalize();

   return 0;
}