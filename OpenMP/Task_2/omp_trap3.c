#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);    /* Function we're integrating */
double Trap(double a, double b, int n, int thread_count);
void printResult(int thread_count, int n,double elapsed_time);

int main(int argc, char* argv[]) {
   double  global_result = 0.0;  /* Store result in global_result */
   double  a, b;                 /* Left and right endpoints      */
   int     n;                    /* Total number of trapezoids    */
   int     thread_count;
   double begin_time, elapsed_time;

   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   
   a=0;
   b=10;
   n=atoi(argv[2]);

   begin_time=omp_get_wtime();

   global_result = Trap(a, b, n, thread_count);

   elapsed_time=omp_get_wtime()-begin_time;

   printResult(thread_count,n,elapsed_time);
   return 0;
}
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
} 

double f(double x) {
   double xx;
   for(int i=0;i<100000;i++){
      xx=x*x;
   }
   return xx;
} 

double Trap(double a, double b, int n, int thread_count) {
   double  h, approx;
   int  i;

   h = (b-a)/n; 
   approx = (f(a) + f(b))/2.0; 
#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: approx)
   for (i = 1; i <= n-1; i++)
     approx += f(a + i*h);
   approx = h*approx; 

   return approx;
}

void printResult(int thread_count, int n,double elapsed_time){
   FILE* file;
   file=fopen("omp_output.txt","a+");
   fprintf(file,"%d - %d - %lf\n", thread_count, n,elapsed_time);
   fclose(file);
}
