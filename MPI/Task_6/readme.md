## Task 6

Question: Write an MPI program that implements multiplication of a vector by a scalar
and dot product. The user should enter two vectors and a scalar, all of which
are read in by process 0 and distributed among the processes. The results are
calculated and collected onto process 0, which prints them. You can assume
that n, the order of the vectors, is evenly divisible by comm sz.
