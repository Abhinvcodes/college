/*
toggle the case of the character in a string indexed by the rank of the process.
author: Abhinav Singh Bhagtana
date: 9 Jan,2026
*/
#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char *argv[])
{
	char string[] = "HeLlOw";
	int rank,size;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	if(size > strlen(string))
	{
		printf("more processes initialized than length of string");
		MPI_Finalize();
		return 0;
	}
	
	if(isupper(string[rank])){
		string[rank] = tolower(string[rank]);
		printf("Process %d: %s\n",rank,string);
	}else{
		string[rank] = toupper(string[rank]);
		printf("Process %d: %s\n",rank,string);
	}
	MPI_Finalize();
	return 0;
}
