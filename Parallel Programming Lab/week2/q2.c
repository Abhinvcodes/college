/*
p0 sends number to every other process which print it.
author: Abhinav Singh Bhagtana
date: 17 Jan, 2026
*/
#include <mpi.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int data,rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank == 0)
	{
		int n = 10;
		for(int i = 1;i < size;i++)
			MPI_Send(&n,1,MPI_INT,i,0,MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("Process %d received %d\n",rank,data);
	}
	MPI_Finalize();
	return 0;
}		
