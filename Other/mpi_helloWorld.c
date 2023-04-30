#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_LENGTH=100;
int main(void){

    char msg[MAX_LENGTH];

    int comm_sz;
    int my_rank;


    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank!=0){

        sprintf(msg,"Hello Worls! I'm process %d of %d",my_rank,comm_sz);
        MPI_Send(msg,strlen(msg)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }else{
        printf("Hello World! I'm process %d of %d\n",my_rank,comm_sz);

        for(int i=1;i<comm_sz;i++){
            MPI_Recv(msg,MAX_LENGTH,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            //MPI_Recv(msg,MAX_LENGTH,MPI_CHAR,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE); -- there's no sequence for receive.
            printf("%s\n",msg);
        }

    }

    
    MPI_Finalize();

    return 0;
}