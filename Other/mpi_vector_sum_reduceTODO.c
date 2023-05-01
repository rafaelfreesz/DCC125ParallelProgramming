#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
const int SIZE=20;

void printVector(int* vector){
    printf("[");
    for(int i=0;i<SIZE-1;i++){
        printf("%d,",*(vector+i));
    }
    printf("%d]\n",vector[SIZE-1]);
}

void printExpected(int* vectorA){
    
    printf("Vector A: ");
    printVector(vectorA);

    int sum=0;
    printf("Expected Sum: ");
    for(int i=0;i<SIZE;i++){
        sum+=vectorA[i];
    }

    printf("%d\n",sum);
}

int main(void){

    int comm_sz, my_rank;
    
    int vectorA[SIZE];
    int vectorB[SIZE];

    for(int i=0;i<SIZE;i++){
        vectorA[i]=i+1;
    }

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if(my_rank==0){
        printExpected(vectorA);
    printf("\n");
    }

    int total_sum;
    MPI_Reduce(vectorA,vectorB,SIZE,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    printf("I'm process %d\n",my_rank);

    if(my_rank==0){
        //printf("Given Sum: %d\n",total_sum);
        for(int i=0;i<SIZE;i++){
            printf("%d,",vectorB[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

}