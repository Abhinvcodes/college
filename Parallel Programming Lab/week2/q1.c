/*
first process sends a string to second process which will toggle the characters and send it back.
use synchronous send.
author: Abhinav Singh Bhagtana
date: 16 Jan, 2026
*/
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toggle_char(char *string)
{
	for(int i = 0; i < strlen(string);i++)
	{
		if(isupper(string[i]))
			string[i] = tolower(string[i]);
		else
			string[i] = toupper(string[i]);
	}
}	

int main(int argc,char *argv[])
{
	int rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	if(rank == 0)
	{
		char string[] = "HELLO";
		char buffer[1024];
		MPI_Ssend(string,strlen(string)+1,MPI_CHAR,1,0,MPI_COMM_WORLD);
		MPI_Recv(buffer,1024,MPI_CHAR,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		printf("recieved string: %s\n",buffer);
	}
	else if(rank == 1)
	{
		char buffer[1024];
		MPI_Recv(buffer,1024,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		toggle_char(buffer);
		MPI_Ssend(buffer,strlen(buffer)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
