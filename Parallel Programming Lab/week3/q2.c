#include <mpi.h>
#include <stdio.h>


double average(double *arr,int size)
{
	double avg = 0;
	for(int i = 0;i < size;i++){
		avg += arr[i];
	}
	return (double)avg/size;
}
int main(int argc,char **argv)
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	int m;
	if(rank == 0) {
	    printf("enter m:\n");
	    //fflush(stdout);
	    scanf("%d",&m);
	}
	
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	double recvarr[100] = {0};
	
	if(rank == 0) {
	    double array[size*m];
	    printf("enter %d elements: \n", size*m);
	    for(int i=0; i<size*m; i++) 
	    	scanf("%lf", &array[i]);
	    MPI_Scatter(array, m, MPI_DOUBLE, recvarr, m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	} else {
	    MPI_Scatter(NULL, m, MPI_DOUBLE, recvarr, m, MPI_DOUBLE, 0, MPI_COMM_WORLD);  // Non-root recv 
	}
	
	printf("process %d recieved numbers:\n",rank);
	for(int i = 0;i < m;i++)
		printf("%f\n",recvarr[i]);
		
	double avg = average(recvarr, m);
	printf("process %d: average = %f\n",rank,avg);

	MPI_Gather(&avg, 1, MPI_DOUBLE, recvarr, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if(rank == 0) {
	    double final_avg = average(recvarr, size);
	    printf("Process 0 calculates average: %f\n", final_avg);
	}
	MPI_Finalize();
	return 0;
}
