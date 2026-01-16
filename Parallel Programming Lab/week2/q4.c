#include <mpi.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(rank == 0)
	{
		int n;
		printf("enter value: ");
		scanf("%d",&n);
		MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
	}
	
	int rcv;
	MPI_Recv(&rcv,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	rcv++;
	if(rank+1 < size)
		MPI_Send(&rcv,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
	else
		MPI_Send(&rcv,1,MPI_INT,0,0,MPI_COMM_WORLD);
		
	if(rank == 0)
	{
		int r;
		MPI_Recv(&r,1,MPI_INT,size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		r++;
		printf("Process 0 received value from last process %d: %d\n",size-1,r);
	}
	MPI_Finalize();
	return 0;
}
