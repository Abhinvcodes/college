/*
print pow(x,rank) where x is a constant. even rank processes print hello, odd print world.
author: Abhinav Singh Bhagtana
date: 9 Jan, 2026
run cmds:
mpicc q1.c -o q1 -lm
mpirun -n 4 ./q1
*/
#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc,char *argv[])
{
	int x = 10;
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	printf("Process %d calculates: %f and says ",rank,pow(x,rank));
	if(rank % 2 == 0)
		printf("Hello\n");
	else
		printf("World\n");
	
	MPI_Finalize();
	return 0;	
	
}
