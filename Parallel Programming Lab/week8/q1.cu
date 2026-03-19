#include "cuda_runtime.h"
#include <stdio.h>

//solving this using a 1D block and 1D grid
__global__ void OneThreadPerRow(int *A, int *B, int *C,int m,int n)
{
	int idx = blockDim.x * blockIdx.x + threadIdx.x;
	//each index corresponds to a row
	if (idx < m)
	{
		//c is the column
		for(int c = 0;c < n;c++)
		{
			C[idx*n + c] = A[idx*n + c] + B[idx*n + c];
		}
	}
}
//solving this using a 1D block and 1D grid
__global__ void OneThreadPerColumn(int *A, int *B, int *C,int m,int n)
{
	int idx = blockDim.x * blockIdx.x + threadIdx.x;
	//each index corresponds to a column
	if (idx < n)
	{
		//k is the row number
		for(int k = 0;k < m;k++)
		{
			C[idx + k * n] = A[idx + k * n] + B[idx + k * n];
		}
	}
}
//solving using 2D block and 1D grid
__global__ void OneThreadPerElement(int *A, int *B, int *C,int m,int n)
{
	int idx = blockIdx.x * (blockDim.x * blockDim.y) + threadIdx.y * blockDim.x + threadIdx.x;
	if(idx < m*n)
		C[idx] = A[idx] + B[idx];
}

int main()
{
	int m,n;
	printf("enter dimensions of matrices: ");
	scanf("%d%d",&m,&n);
	
	int A[m][n],B[m][n],C[m][n];
	int *d_A,*d_B,*d_C;
	int size = sizeof(int)*m*n;
	
	printf("enter values for matrix A:\n");
	for(int i = 0;i < m;i++)
		for(int j = 0;j<n;j++)
			scanf("%d",&A[i][j]);
	printf("enter values for matrix B:\n");
	for(int i = 0;i < m;i++)
		for(int j = 0;j<n;j++)
			scanf("%d",&B[i][j]);
	
	//tell the gpu to allocate space
	cudaMalloc((void**)&d_A,size);
	cudaMalloc((void**)&d_B,size);
	cudaMalloc((void**)&d_C,size);
	
	//copy A and B to gpu memory
	cudaMemcpy(d_A,A,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_B,B,size,cudaMemcpyHostToDevice);
	
	//call Kernels
	printf("Result computed using one thread per row\n");
	dim3 block1(256);
	dim3 grid1((m * n + 255) / 256);
	OneThreadPerRow<<<grid1,block1>>>(d_A,d_B,d_C,m,n);
	cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);
	for(int i =0;i < m;i++){
		for(int j=0;j<n;j++)
			printf("%d\t",C[i][j]);
		printf("\n");
	}
	
	printf("Result computed using one thread per row\n");
	dim3 grid2((n + 255) / 256);
	OneThreadPerColumn<<<grid2, block1>>>(d_A, d_B, d_C, m, n);
	cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);
	for(int i =0;i < m;i++){
		for(int j=0;j<n;j++)
			printf("%d\t",C[i][j]);
		printf("\n");
	}
	
	printf("Result computed using one thread per element\n");
	dim3 block(m,n);
	dim3 grid(1);
	OneThreadPerElement<<<grid,block>>>(d_A,d_B,d_C,m,n);
	cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);
	for(int i =0;i < m;i++){
		for(int j=0;j<n;j++)
			printf("%d\t",C[i][j]);
		printf("\n");
	}
	
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
	return 0;
}

