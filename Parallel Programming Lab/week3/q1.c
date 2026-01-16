#include <mpi.h>
#include <stdio.h>

int fact(int n)
{
	int p = 1;
	for(int i = 2; i <= n;i++)
		p*=i;
	return p;
}

int main(int argc,char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	int n, array[size];
	if(rank == 0)
	{
		
		printf("enter %d values: ",size);
		for(int i = 0;i < size;i++)
			scanf("%d",&array[i]);
	}
	MPI_Scatter(array,1,MPI_INT,&n,1,MPI_INT,0,MPI_COMM_WORLD);
	n = fact(n);
	MPI_Gather(&n,1,MPI_INT,array,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank == 0)
	{	
		int sum = 0;
		for(int i = 0;i < size;i++)
			sum+=array[i];
		printf("process 0 has calculateds sum: %d\n",sum);
	}
	MPI_Finalize();
	return 0;
}
