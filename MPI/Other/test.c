#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIZE 10

int main(int argc, char** argv) {
  int my_rank, comm_size;
  int local_size;
  int vectorA[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int vectorB[SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int vectorC[SIZE]; // vetor resultante da soma de A e B

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  // Divide os vetores em partes iguais para cada processo
  local_size = SIZE / comm_size;

  // Soma os elementos correspondentes de A e B em C
  int local_start = my_rank * local_size;
  for (int i = local_start; i < local_start + local_size; i++) {
    vectorC[i] = vectorA[i] + vectorB[i];
  }

  // Usa MPI_Reduce para somar os elementos de C em um único resultado
  int global_sum;
  MPI_Reduce(vectorC, &global_sum, SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Imprime o resultado final
  if (my_rank == 0) {
    printf("A soma dos elementos dos vetores A e B é %d\n", global_sum);
  }

  MPI_Finalize();
  return 0;
}