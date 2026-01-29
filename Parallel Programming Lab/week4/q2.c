#include <stdio.h>
#include <mpi.h>

int main(int argc,char **argv)
{
	int rank = 0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int mat[3][3] = {0};
	int destarr[3] = {0};
	int count = 0;
	int find;
	int totalcount = 0;
	
	if(rank == 0){
		printf("enter a 3x3 matrix\n");
		for(int i = 0;i < 3;i++)
			for(int j = 0;j<3;j++)
				scanf("%d",&mat[i][j]);
		printf("enter an element to find:\n");
		scanf("%d",&find);
	}
	
	//sending the number to find
	MPI_Bcast(&find,1,MPI_INT,0,MPI_COMM_WORLD);
	//sending the rows
	MPI_Scatter(mat,3,MPI_INT,destarr,3,MPI_INT,0,MPI_COMM_WORLD);
	//finding the element
	for(int i = 0;i < 3;i++)
		if(destarr[i] == find)
			count++;
	MPI_Reduce(&count,&totalcount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank == 0)
		printf("total occurences of %d = %d",find,totalcount);
	MPI_Finalize();
	return 0;
}
