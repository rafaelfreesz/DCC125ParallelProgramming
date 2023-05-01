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

    int local_begin, local_n, comm_sz, my_rank;
    
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

    int *local_Vector=(int*) malloc(local_n*sizeof(int));
    
    for(int i=0;i<local_n;i++){
        local_Vector[i]=vectorA[local_begin+i]+vectorB[local_begin+i];
    }

    if(my_rank!=0){
        MPI_Send(local_Vector,local_n,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{

        for(int i=0;i<local_n;i++){
            vectorC[i]=local_Vector[i];
        }

        for(int i=1;i<comm_sz;i++){
            MPI_Recv(local_Vector,local_n,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

            for(int j=0;j<local_n;j++){
                vectorC[i*local_n+j]=local_Vector[j];
            }
        }

        printf("Given Vector C:[");
        for(int i=0;i<SIZE-1;i++){
            printf("%d,",vectorC[i]);
        }
        printf("%d]\n",vectorC[SIZE-1]);
    }

    MPI_Finalize();

}