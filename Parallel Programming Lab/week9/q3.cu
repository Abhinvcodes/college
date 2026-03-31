#include "cuda_runtime.h"
#include <stdio.h>

__global__ void kernel(int *A, int *B, int m, int n)
{
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	if( row >= m || col >= n)
		return;
	if( row != 0 && row != m-1 && col != 0 && col != n-1 )
	{
		int x = A[row * n + col];
		int bits = (x == 0) ? 1 : (32 - __clz(x));
        	int ones_comp = (~x) & ((1 << bits) - 1);
		B[row * n + col] = ones_comp;
	}
	else
		B[row * n + col] = A[row * n + col];
}
int main()
{
	int m,n;
	printf("enter dimensions:\n");
	scanf("%d%d",&m,&n);
	
	int A[m][n],B[m][n],*d_A,*d_B;
	printf("enter matrix (%dx%d):\n",m,n);
	for(int i = 0;i < m;i++)
		for(int j =0;j<n;j++)
			scanf("%d",&A[i][j]);
	int size = sizeof(int)*m*n;
	
	cudaMalloc(&d_A,size);
	cudaMalloc(&d_B,size);
	
	cudaMemcpy(d_A,A,size,cudaMemcpyHostToDevice);
	
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
