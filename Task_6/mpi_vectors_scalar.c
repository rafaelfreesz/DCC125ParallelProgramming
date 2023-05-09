#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void getDim(int* n,int* local_n, int my_rank, int comm_sz, MPI_Comm comm);
void readScalar(int* scalar,int my_rank, MPI_Comm comm);
void allocateVectors(int** local_va, int** local_vb, int** local_vc, int local_n);
void readVector(int* local_v, int n,int local_n, int my_rank,char* vName, MPI_Comm comm);
void calcDotProduct(int* local_va,int* local_vb, int* local_result, int local_n); 
void calcScalarProduct(int* local_va, int* local_vc,int scalar, int local_n);
void printResult(int* local_vc, int total_result, int local_n, int n, int my_rank, MPI_Comm comm);

int main(void){
    int n, comm_sz, my_rank, scalar, local_n, local_result, total_result=0;
    int *local_va, *local_vb, *local_vc;
    MPI_Comm comm=MPI_COMM_WORLD;

    MPI_Init(NULL,NULL);
    MPI_Comm_size(comm,&comm_sz);
    MPI_Comm_rank(comm,&my_rank);
    
    getDim(&n, &local_n,my_rank, comm_sz, comm);
    allocateVectors(&local_va,&local_vb,&local_vc,local_n);
    readScalar(&scalar,my_rank,comm);
    //Reading vector B
    readVector(local_va,n,local_n,my_rank,"A", comm);
    //Reading vector B
    readVector(local_vb,n,local_n,my_rank,"B", comm);

    calcDotProduct(local_va,local_vb,&local_result,local_n);
    MPI_Reduce(&local_result,&total_result,1,MPI_INT,MPI_SUM,0,comm);

    calcScalarProduct(local_va,local_vc,scalar,local_n);

    printResult(local_vc,total_result,local_n,n,my_rank,comm);

    

    free(local_va);
    free(local_vb);
    free(local_vc);
    MPI_Finalize();
}

//Setting n
void getDim(int* n, int* local_n, int my_rank, int comm_sz, MPI_Comm comm){
    if(my_rank==0){
        printf("Enter vectors size: \n");
        scanf("%d",n);
    
        *local_n=*n/comm_sz;
    }
    
    MPI_Bcast(n,1,MPI_INT,0,comm);
    MPI_Bcast(local_n,1,MPI_INT,0,comm);
}

//Reading Scalar
void readScalar(int* scalar,int my_rank, MPI_Comm comm){
    if(my_rank==0){
        printf("Enter the scalar: \n");
        scanf("%d",scalar);  
    }

    MPI_Bcast(scalar,1,MPI_INT,0,comm);
}

//Allocating local vectors
void allocateVectors(int** local_va, int** local_vb, int** local_vc, int local_n){
    
    *local_va=malloc(local_n*sizeof(int));
    *local_vb=malloc(local_n*sizeof(int));
    *local_vc=malloc(local_n*sizeof(int));
}

//Reading and scattering vectors
void readVector(int* local_v, int n,int local_n, int my_rank,char* vName, MPI_Comm comm){
        int * vector=NULL;

        if(local_v==NULL){
            printf("local_v is null\n");
            exit(1);
        }

        if(my_rank==0){
            vector=malloc(n*sizeof(int));
            printf("Enter vector %s integer values:\n",vName);
            for(int i=0;i<n;i++){
                scanf("%d",&vector[i]);
            }
            MPI_Scatter(vector,local_n,MPI_INT,local_v,local_n,MPI_INT,0,comm);
            free(vector);
        }else{
            MPI_Scatter(vector,local_n,MPI_INT,local_v,local_n,MPI_INT,0,comm);
        }

}

//Calculating dotProduct
void calcDotProduct(int* local_va,int* local_vb, int* local_result, int local_n){
    *local_result=0;
    for(int i=0;i<local_n;i++){
        *local_result+=local_va[i]*local_vb[i];
    }
}

//Calculating scalar product
void calcScalarProduct(int* local_va, int* local_vc, int scalar, int local_n){
    for(int i=0;i<local_n;i++){
        local_vc[i]=scalar*local_va[i];
    }
}

//Gather and print
void printResult(int* local_vc, int total_result, int local_n,int n,int my_rank, MPI_Comm comm){
    int* resultVector=NULL;
    if(my_rank==0){
        printf("Dot product result = %d\n",total_result);
        
        resultVector=malloc(n*sizeof(int));

        MPI_Gather(local_vc,local_n,MPI_INT,resultVector,local_n,MPI_INT,0,comm);

        printf("Result vector:\n");
        for(int i=0;i<n;i++){
            printf("%d, ",resultVector[i]);
        }
        printf("\n");   
        free(resultVector);
    }else{
        MPI_Gather(local_vc,local_n,MPI_INT,resultVector,local_n,MPI_INT,0,comm);
    }
}