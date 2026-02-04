#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	int matrix[4][4] = {0};
	int row[4] = {0};
	int prefixSum[4] = {0};
	
	if(rank == 0){
		printf("enter a 4x4 matrix\n");
		for(int i = 0;i < 4;i++)
			for(int j = 0; j < 4;j++)
				scanf("%d",&matrix[i][j]);
	}
	MPI_Scatter(matrix,4,MPI_INT,row,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scan(row,prefixSum,4,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	for(int i = 0;i < 4;i++)
		printf("%d\t",prefixSum[i]);
	printf("\n");
	MPI_Finalize();
	return 0;
}
