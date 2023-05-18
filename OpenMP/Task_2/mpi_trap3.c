#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

void Get_input(int my_rank, int comm_sz, int n ,double* a_p, double* b_p, int* n_p);

double Trap(double left_endpt, double right_endpt, int trap_count, double base_len);

void printResult(int comm_sz, int n,double elapsed_time);

double f(double x); 

int main(int argc, char* argv[]) {
   int my_rank, comm_sz, n, local_n;   
   double a, b, h, local_a, local_b, begin_time, elapsed_time, max_time;
   double local_int, total_int;

   MPI_Init(NULL, NULL);

   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   Get_input(my_rank, comm_sz, atoi(argv[1]),&a, &b, &n);

   h = (b-a)/n;          /* h is the same for all processes */
   local_n = n/comm_sz;  /* So is the number of trapezoids  */

   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*h;

   MPI_Barrier(MPI_COMM_WORLD);
   begin_time=MPI_Wtime();
   
   local_int = Trap(local_a, local_b, local_n, h);

   MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   elapsed_time=MPI_Wtime()-begin_time;

   MPI_Reduce(&elapsed_time,&max_time,1,MPI_DOUBLE,MPI_MAX,0, MPI_COMM_WORLD);

   MPI_Barrier(MPI_COMM_WORLD);

   if (my_rank == 0) {
      printResult(comm_sz,n,max_time);
   }

   MPI_Finalize();

   return 0;
} /*  main  */

void printResult(int comm_sz, int n,double elapsed_time){
   FILE* file;
   file=fopen("mpi_output.txt","a+");
   fprintf(file,"%d - %d - %lf\n", comm_sz, n,elapsed_time);
   fclose(file);
}

void Get_input(int my_rank, int comm_sz, int n, double* a_p, double* b_p,
      int* n_p) {

   if (my_rank == 0) {
      *n_p=n;
      *a_p=0;
      *b_p=10;
   } 
   MPI_Bcast(a_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(b_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

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
}

double f(double x) {
   double xx;
   for(int i=0;i<100000;i++){
      xx=x*x;
   }
   return xx;
} /* f */
