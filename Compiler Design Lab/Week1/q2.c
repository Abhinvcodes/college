/*
write a simple calculator using mpi where different thread does different operations
author: Abhinav Singh Bhagtana
date: 9 Jan, 2026
*/
#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[])
{
	int a=543,b=234,rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	if(rank == 0)
		printf("Process %d: %d + %d = %d\n",rank,a,b,a+b);
	else if(rank == 1)
		printf("Process %d: %d - %d = %d\n",rank,a,b,a-b);
	else if(rank == 2)
		printf("Process %d: %d * %d = %d\n",rank,a,b,a*b);
	else if(rank == 3)
		printf("Process %d: %d / %d = %f\n",rank,a,b,(float)a/b);
	else
		printf("this thread does not do anything");
	MPI_Finalize();
	return 0;
}
