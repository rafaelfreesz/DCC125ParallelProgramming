#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
const int SIZE=10;

void printVector(int* vector){
    printf("[");
    for(int i=0;i<SIZE-1;i++){
        printf("%d,",vector[i]);
    }
    printf("%d]\n",vector[SIZE-1]);
}

void printExpected(int* vectorA, int*vectorB){
    
    printf("Vector A: ");
    printVector(vectorA);
    printf("Vector B: ");
    printVector(vectorB);

    printf("Expected Vector C: [");
    for(int i=0;i<SIZE-1;i++){
        printf("%d,",vectorA[i]+vectorB[i]);
    }

    printf("%d]\n",(vectorA[SIZE-1]+vectorB[SIZE-1]));
}

int main(void){

    int local_begin, local_end, local_n, comm_sz, my_rank;
    
    int vectorA[SIZE], vectorB[SIZE], vectorC[SIZE];

    for(int i=0;i<SIZE;i++){
        vectorA[i]=i+1;
        vectorB[i]=SIZE+i+1;
    }

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if(my_rank==0){
        printExpected(vectorA,vectorB);
    }

    local_n=SIZE/comm_sz;
    local_begin=local_n*my_rank;
    local_end=local_begin+local_n;

    for(int i=local_begin;i<local_end;i++){
        vectorC[i]=vectorA[i];
    }

    MPI_Reduce(vectorB,vectorC,local_n,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(my_rank==0){
        printf("Given Vector C:[");
        for(int i=0;i<SIZE-1;i++){
            printf("%d,",vectorC[i]);
        }
        printf("%d]\n",vectorC[SIZE-1]);
    }

    MPI_Finalize();

}