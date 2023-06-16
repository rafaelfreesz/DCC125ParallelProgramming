/* File:     mpi_trap1.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal 
 *           rule.  In this version the endpoints of the interval and
 *           the number of trapezoids are hardwired.
 *
 * Input:    None.
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o mpi_trap1 mpi_trap1.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap1
 *
 * Algorithm:
 *    1.  Each process calculates "its" interval of
 *        integration.
 *    2.  Each process estimates the integral of f(x)
 *        over its interval using the trapezoidal rule.
 *    3a. Each process != 0 sends its integral to 0.
 *    3b. Process 0 sums the calculations received from
 *        the individual processes and prints the result.
 *
 * Note:  f(x), a, b, and n are all hardwired.
 *
 * IPP:   Section 3.2.2 (pp. 96 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mpi.h>

double Trap(double left_endpt, double right_endpt, int trap_count, 
   double base_len); 
double f(double x); 
void printResult(int comm_sz, int n,double result, double elapsed_time);
void verifyInterval(int comm_sz,int my_rank,double local_a, double local_b);
int buildLimits(int my_rank, double* local_a, double* local_b, double* before_b, int a,double h, int comm_sz, int n);

int main(int argc, char* argv[]) {


   int my_rank, comm_sz, n = atoi(argv[1]), local_n;   
   double a = 0.0, b = 3.0, h, local_a, local_b, before_b;
   double local_int, total_int, begin_time, end_time, elapsed_time;
   int source;
   MPI_Comm comm= MPI_COMM_WORLD;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(comm, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(comm, &comm_sz);

   h = (b-a)/n;          /* h is the same for all processes */  

   local_n = buildLimits(my_rank,&local_a,&local_b,&before_b,a,h,comm_sz,n);

   local_int = Trap(local_a, local_b, local_n, h);

   MPI_Barrier(comm);


   begin_time=MPI_Wtime();

   local_int = Trap(local_a, local_b, local_n, h);

   /* Add up the integrals calculated by each process */
   if (my_rank != 0) { 
      MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, 
            MPI_COMM_WORLD);
   } else {
      total_int = local_int;
      for (source = 1; source < comm_sz; source++) {
         MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         total_int += local_int;
      }
   } 

   end_time=MPI_Wtime();
   elapsed_time=end_time-begin_time;

   /* Print the result */
   if (my_rank == 0) {
     printResult(comm_sz,n,total_int,elapsed_time);
   }

   /* Shut down MPI */
   MPI_Finalize();


   return 0;
} /*  main  */


/*------------------------------------------------------------------
 * Function:     Trap
 * Purpose:      Serial function for estimating a definite integral 
 *               using the trapezoidal rule
 * Input args:   left_endpt
 *               right_endpt
 *               trap_count 
 *               base_len
 * Return val:   Trapezoidal rule estimate of integral from
 *               left_endpt to right_endpt using trap_count
 *               trapezoids
 */
double Trap(
      double left_endpt  /* in */, 
      double right_endpt /* in */, 
      int    trap_count  /* in */, 
      double base_len    /* in */) {
   double estimate, x; 
   int i;

   estimate = (f(left_endpt) + f(right_endpt))/2.0;
   for (i = 1; i <= trap_count-1; i++) {
      x = left_endpt + i*base_len;
      estimate += f(x);
   }
   estimate = estimate*base_len;

   return estimate;
} /*  Trap  */


/*------------------------------------------------------------------
 * Function:    f
 * Purpose:     Compute value of function to be integrated
 * Input args:  x
 */
double f(double x) {
   double res=x*x;
  
   for(int i=0;i<2000000;i++){
      res=x/x;
      res=x*x;
   }

   return res;
} /* f */

void printResult(int comm_sz, int n,double result, double elapsed_time){
   FILE* file;
   file=fopen("mpi_trap1_output.txt","a+");
   fprintf(file,"%d - %d - %lf - %lf\n", comm_sz, n,result,elapsed_time);
   fclose(file);
}

void verifyInterval(int comm_sz,int my_rank,double local_a, double local_b){
   
      char msg[200];
   if(my_rank!=0){
      sprintf(msg,"I'm process %d, my [local_a,local_b] is [%lf,%lf]. d=%lf",my_rank,local_a,local_b,local_b-local_a);
      MPI_Send(msg,strlen(msg)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);

   }else{
      printf("I'm process %d, my [local_a,local_b] is [%lf,%lf]. d=%lf\n",my_rank,local_a,local_b,local_b-local_a);
      for(int i=1;i<comm_sz;i++){
         MPI_Recv(msg,200,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
         printf("%s\n",msg);
      }

   }

}

int buildLimits(int my_rank, double* local_a, double* local_b, double* before_b, int a,double h, int comm_sz, int n){
   int local_n = n/comm_sz;

if(my_rank==0){
      *local_a = a + my_rank* local_n*h;
      *local_b = *local_a + local_n*h;

   }else{
      MPI_Recv(before_b,1,MPI_DOUBLE,my_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      *local_a=*before_b;
      *local_b=*local_a+local_n*h;

      if(my_rank>=comm_sz-n%comm_sz){
         local_n++;
         *local_b+=h;
      }

   }

   if(my_rank!=(comm_sz-1)){
      MPI_Send(&local_b,1,MPI_DOUBLE,my_rank+1,0,MPI_COMM_WORLD);
   }

   return local_n;

}
