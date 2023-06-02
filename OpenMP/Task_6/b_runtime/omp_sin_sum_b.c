/* File:    omp_sin_sum.c
 * Purpose: Compute a sum in which each term is the value of a function
 *          applied to a nonnegative integer i and evaluation of the
 *          function requires work proportional to i.
 *
 * Compile: gcc -g -Wall -fopenmp -I. -o omp_sin_sum omp_sin_sum.c
 * Usage:   ./omp_sin_sum <number of threads> <number of terms>
 *
 * Input:   none
 * Output:  sum of n terms and elapsed time to compute the sum
 *
 * Notes:
 * 1.  The computed sum is
 *
 *        sin(0) + sin(1) + . . . + sin(n(n+3)/2)
 *
 * 2.  The function f(i) is
 *
 *        sin(i(i+1)/2) + sin(i(i+1)/2 + 1) + . . . + sin(i(i+1)/2 + i)
 *
 * 3.  The parallel for directive uses a runtime schedule clause. So
 *     the environment variable OMP_SCHEDULE should be either
 *     "static,n/thread_count" for a block schedule or "static,1"
 *     for a cyclic schedule
 * 4.  Uses the OpenMP library function omp_get_wtime to take timings.
 * 5.  DEBUG flag will print which iterations were assigned to each
 *     thread.
 *
 * IPP:  Section 5.7 (pp. 236 and ff.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#ifdef DEBUG
int*    iterations;
#endif

void Usage(char* prog_name);
double Sum(long n, int thread_count);
double Check_sum(long n, int thread_count);
double f(long i);
double f2(long i);
void Print_iters(int iterations[], long n);
void printResult(int thread_count, int n,double result, double elapsed_time);

int main(int argc, char* argv[]) {
   double  global_result;        /* Store result in global_result */
   long    n;                    /* Number of terms               */
   int     thread_count;
   double  start, finish;

   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   n = strtol(argv[2], NULL, 10);
#  ifdef DEBUG
   iterations = malloc((n+1)*sizeof(int));
#  endif

   start = omp_get_wtime();
   global_result = Sum(n, thread_count);
   finish = omp_get_wtime();
   
   printf("%lf\n",global_result);


   printResult(strtol(argv[1], NULL, 10),n,global_result,finish-start);

#  ifdef DEBUG
   Print_iters(iterations, n);
   free(iterations);
#  endif

   return 0;
}  /* main */

/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads> <number of terms>\n",
         prog_name);
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function in which work is
 *              proportional to the size of the first arg.
 * Input arg:   i, n
 * Return val:  
 */
double f(long i) {
   
   double return_val = 0.0;
   double val=(double)i;
     
   for(int k=i-1;k>0;k--){
      val*=(double)i;
      val/=(double)i;
      return_val+=val;
   }
   
   return return_val;
}  /* f */

double f2(long i) {
   
   double return_val = 0.0;
     
   for(size_t j=0; j<i; j++){
      return_val+=1.f/i;
   }
   
   return return_val;
}  /* f */

/*------------------------------------------------------------------
 * Function:    Sum
 * Purpose:     Find the sum of the terms f(0), f(1), . . ., f(n),
 *              where evaluating f requires work proportional to
 *              its argument
 * Input args:  
 *    n: number of terms
 *    thread_count:  number of threads
 * Return val:
 *    approx:  f(0) + f(1) + . . . + f(n)
 */
double Sum(long n, int thread_count) {
   double approx = 0.0;
   long i;
   
   unsigned int l=0;
   

#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: approx) shared(l) private(i) schedule(dynamic,4)
   for (i = 0; i <= n; i++) {
     approx += f(rand_r(&l)%10);
     
   }

   return approx;
}  /* Sum */


void printResult(int thread_count, int n,double result, double elapsed_time){
   FILE* file;
   file=fopen("omp_a_b_output.txt","a+");
   fprintf(file,"%d - %d - %lf - %lf\n", thread_count, n,result,elapsed_time);
   fclose(file);
}


/*------------------------------------------------------------------
 * Function:  Print_iters
 * Purpose:   Print which thread was assigned which iteration.
 * Input args:  
 *    iterations:  iterations[i] = thread assigned iteration i
 *    n:           size of iterations array
 */
void Print_iters(int iterations[], long n) {
   int i, start_iter, stop_iter, which_thread;

   printf("\n");
   printf("Thread\t\tIterations\n");
   printf("------\t\t----------\n");
   which_thread = iterations[0];
   start_iter = stop_iter = 0;
   for (i = 0; i <= n; i++)
      if (iterations[i] == which_thread)
         stop_iter = i;
      else {
         printf("%4d  \t\t%d -- %d\n", which_thread, start_iter,
               stop_iter);
         which_thread = iterations[i];
         start_iter = stop_iter = i;
      }
   printf("%4d  \t\t%d -- %d\n", which_thread, start_iter,
               stop_iter);
}  /* Print_iters */