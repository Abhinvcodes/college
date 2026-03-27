#include "cuda_runtime.h"
#include <stdio.h>
#include <math.h>

__global__ void kernel(int *A, int *B, int m, int n)
{
	int row = blockIdx.x * blockDim.x + threadIdx.x;
	int col = blockIdx.y * blockDim.y + threadIdx.y;
	if(row >= m || col >= n)
		return;
	B[row*n + col] = ceil(pow(A[row*n+col],row+1));
}

int main()
{
	int m,n;
	printf("enter dimensions: ");
	scanf("%d %d",&m,&n);
	
	int A[m][n],B[m][n],*d_A,*d_B;
	printf("enter A (%dx%d):\n",m,n);
	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++)
			scanf("%d",&A[i][j]);
	
	cudaMalloc(&d_A,sizeof(int) * m * n);
	cudaMalloc(&d_B,sizeof(int) * m * n);
	
	cudaMemcpy(d_A,A,sizeof(int) * m * n, cudaMemcpyHostToDevice);
	dim3 block(16,16);
	dim3 grid((m+15)/16.0,(n+15)/16.0);
	kernel<<<grid,block>>>(d_A,d_B,m,n);
	
	cudaMemcpy(B,d_B,sizeof(int) * m * n, cudaMemcpyDeviceToHost);
	
	printf("Resultant matrix:\n");
	for(int i = 0;i < m;i++){
		for(int j = 0;j < n;j++)
			printf("%d\t",B[i][j]);
		printf("\n");	
	}
	cudaFree(d_A);
	cudaFree(d_B);
	return 0;
}
