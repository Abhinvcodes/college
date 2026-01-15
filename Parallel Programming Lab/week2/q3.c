#include <mpi.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int size,rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	int buffer[1023];
	int buf_size = 1023*sizeof(int);
	if(rank == 0)
	{
		int array[size];
		for(int i= 0;i < size;i++)
			array[i] = i;
		
		MPI_Buffer_attach(buffer,1023*sizeof(int));
		
		for(int i = 1;i < size;i++)
			MPI_Bsend(&array[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
			
	}
	int n;
	
	
	if(rank == 0){
		n = 0;
		printf("Process %d: %d\n",rank,n);
	}
	else{
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		if(rank % 2 == 0)
		{
			n = n*n;
			printf("Process %d: %d\n",rank,n);
		}
		else
		{
			n = n*n*n;
			printf("Process %d: %d\n",rank,n);
		}
	}
	if(rank == 0)
	{
		void *dummy;
		int dummy_size;
		MPI_Buffer_detach(&dummy,&dummy_size);
	}
	
	MPI_Finalize();
	return 0;
}
