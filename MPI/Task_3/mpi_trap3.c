/* File:     mpi_trap3.c
 * Purpose:  Use MPI to implement a parallel version of the trapezoidal 
 *           rule.  This version uses collective communications to 
 *           distribute the input data and compute the global sum.
 *
 * Input:    The endpoints of the interval of integration and the number
 *           of trapezoids
 * Output:   Estimate of the integral from a to b of f(x)
 *           using the trapezoidal rule and n trapezoids.
 *
 * Compile:  mpicc -g -Wall -o mpi_trap2 mpi_trap2.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap2
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
 * Note:  f(x) is all hardwired.
 *
 * IPP:   Section 3.4.2 (pp. 104 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mpi.h>

/* Get the input values */
void Get_input(int my_rank, int comm_sz, double* a_p, double* b_p,
      int* n_p);

/* Calculate local integral  */
double Trap(double left_endpt, double right_endpt, int trap_count, 
   double base_len);    

/* Function we're integrating */
double f(double x); 
void printResult(int comm_sz, int n,double result, double elapsed_time);
void verifyInterval(int comm_sz,int my_rank,double local_a, double local_b);

int main(int argc, char* argv[]) {
   int my_rank, comm_sz, n = atoi(argv[1]), local_n;   
   double a=0.0, b=3.0, h, local_a, local_b, begin_time, end_time, elapsed_time;
   double local_int, total_int;

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   h = (b-a)/n;          /* h is the same for all processes */
   local_n = n/comm_sz;

   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;

   //verifyInterval(comm_sz,my_rank,local_a,local_b);

   MPI_Barrier(MPI_COMM_WORLD);

   begin_time=MPI_Wtime();
   
   local_int = Trap(local_a, local_b, local_n, h);

   /* Add up the integrals calculated by each process */
   MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
         MPI_COMM_WORLD);

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
   double estimate,x; 
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
   int y=(int)x;
   for(int i=y*y*y*y*y*y*y*y*y*y;i>0;i--){
      for(int j=0;j<y*y*y*y*y*y*y*y*y;j++){
         res=x/x;
         res=x*x;
      }
   }

   return res;
} /* f */

void printResult(int comm_sz, int n,double result, double elapsed_time){
   FILE* file;
   file=fopen("mpi_trap3_output.txt","a+");
   fprintf(file,"%d - %d - %lf - %lf\n", comm_sz, n,result,elapsed_time);
   fclose(file);
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
      MPI_Send(local_b,1,MPI_DOUBLE,my_rank+1,0,MPI_COMM_WORLD);
   }

   return local_n;

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