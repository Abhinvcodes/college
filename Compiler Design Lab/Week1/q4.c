/*
even process prints factorial of rank and odd process prints rank fibonacci number
author: Abhinav Singh Bhagtana
date: 9 Jan,2026
*/
#include <mpi.h>
#include <stdio.h>

int fact(int n)
{
	int f = 1;
	for(int i = 1;i <= n;i++)
		f *= i;
	return f;
}

int fib(int n) {
    if (n <= 1) return n; 
    
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) { 
        c = a + b;
        a = b;
        b = c;
    }
    return b; 
}



int main(int argc,char *argv[])
{
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	if(rank % 2 == 0)
		printf("Process %d: factorial of %d = %d\n",rank,rank,fact(rank));
	else
		printf("Process %d: %d fibonacci number = %d\n",rank,rank,fib(rank));
	
	MPI_Finalize();
	return 0;
}
