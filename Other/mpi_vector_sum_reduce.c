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

void printExpected(int* vectorA,int* vectorB){
    
    printf("Vector A: ");
    printVector(vectorA);
    printf("Vector B: ");
    printVector(vectorB);

    printf("Expected Vector C: [");
    for(int i=0;i<SIZE-1;i++){
        printf("%d,",vectorA[i]+vectorB[i]);
    }

    printf("%d]\n",vectorA[SIZE-1]+vectorB[SIZE-1]);
}
void buildVector()
int main(void){

    int comm_sz, my_rank;
    
    int vectorA[SIZE/comm_sz];
    int vectorB[SIZE/comm_sz];
    int vectorC[SIZE];


    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    int local_n=SIZE/comm_sz;


    if(my_rank==0){
        for(int i=0;i<SIZE;i++){
            vectorA[i]=i+1;
            vectorB[i]=SIZE+i+1;
        }
        printExpected(vectorA,vectorB);
        printf("\n");

        MPI_Scatter(vectorC,local_n,MPI_INT,)
    }

    


    if(my_rank==0){
        printf("Given Vector C: [");
        for(int i=0;i<SIZE-1;i++){
            printf("%d,",vectorC[i]);
        }
        printf("%d]\n",vectorC[SIZE-1]);
    }

    MPI_Finalize();

}