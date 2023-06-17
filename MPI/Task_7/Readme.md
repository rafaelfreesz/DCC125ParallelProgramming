## Task 7

Modificar o código paralelo para ordenação de forma que antes de cada iteracao ou fase seja feita, em paralelo, a verificação se as chaves já estão ordenadas de forma distribuída.

## Solução

Função implementada para verificação

```c
void isOrdenado(int my_rank, int local_A[], int local_n, short* ord, int p){

   int last_before=-1;

   if(my_rank!=0){
       MPI_Recv(&last_before,1,MPI_INT,my_rank-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);  
      if(last_before>local_A[0]){

         *ord=0;
         printf("Process %d. Ainda falta ordenar!\n",my_rank);
         MPI_Bcast(ord,1,MPI_SHORT,my_rank,MPI_COMM_WORLD);

         if(my_rank<p-1){
            MPI_Send(&local_A[local_n-1],1,MPI_INT,my_rank+1,1,MPI_COMM_WORLD);
         }

         return;
      }
   }

   for(int i=1;i<local_n; i++){

      if(local_A[i]<local_A[i-1]){
         *ord=0;
         printf("Process %d. Ainda falta ordenar!\n",my_rank);
         break;
      }

   }

   MPI_Bcast(ord,1,MPI_SHORT,my_rank,MPI_COMM_WORLD);

   if(my_rank<p-1){
      MPI_Send(&local_A[local_n-1],1,MPI_INT,my_rank+1,1,MPI_COMM_WORLD);
   }
   
   printf("Process %d. FIZ!\n",my_rank);

}
```