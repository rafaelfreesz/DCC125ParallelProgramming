#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void getArg(long long int* nuLancamentos,int* threadCount, int argc, char** argv);
long monteCarlo(long long int nuLancamentos, double*piEst, int threadCount, double* tempoDecorrido);
void printResult(int thread_count, long long int n,double result, double elapsed_time);


int main(int argc, char* argv[]){

    long long int nuLancamentos,nuCirculo;
    double piEst, tempo;
    int threadCount;

    getArg(&nuLancamentos, &threadCount,argc,argv);

    nuCirculo=monteCarlo(nuLancamentos, &piEst, threadCount, &tempo);


    printResult(threadCount,nuLancamentos,piEst,tempo);


    printf("piEst=%lf, nuLancamento=%lld, nuCirculo=%lld\n",piEst,nuLancamentos,nuCirculo);


    return 0;
}

void printResult(int thread_count, long long int n,double result, double elapsed_time){
   FILE* file;
   file=fopen("omp_pi_output.txt","a+");
   fprintf(file,"%d - %lld - %lf - %lf\n", thread_count, n,result,elapsed_time);
   fclose(file);
}

long monteCarlo(long long int nuLancamentos, double*piEst, int threadCount, double* tempoDecorrido){

    long nuCirculo=0;
    long lancamento;
    double tempoInicio, tempoFinal;

    long seed=100;
    struct drand48_data randBuffer;

    srand48_r(seed,&randBuffer);

    tempoInicio=omp_get_wtime();

   # pragma omp parallel for num_threads(threadCount) \
        default(none) private(lancamento) shared(nuCirculo, nuLancamentos, randBuffer)
    for(lancamento=0;lancamento<nuLancamentos;lancamento++){

        double x;
        double y;

        drand48_r(&randBuffer,&x);
        drand48_r(&randBuffer,&y);

        x=-1.0+2.0*x;
        y=-1.0+2.0*y;

        double distQuad=x*x+y*y;

        if(distQuad<=1.0){
            nuCirculo++;
        }

    }

    tempoFinal=omp_get_wtime();
    *tempoDecorrido=tempoFinal-tempoInicio;

    *piEst=4*((double)nuCirculo)/(double)nuLancamentos;

    return nuCirculo;

}

//Atribui os argumentos necessários vindos de argv
void getArg(long long int* nuLancamentos,int* threadCount, int argc, char** argv){
    if(argc<3){
        printf("Argumentos insuficientes\n");
        exit(1);
    }else{
        *nuLancamentos=atol(argv[2]);
        *threadCount=atoi(argv[1]);
    }
}