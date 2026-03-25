#include "cuda_runtime.h"
#include <stdio.h>

__global__ void odd(int *a,int len)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if( i % 2 != 0 && i < len - 1 && a[i] < a[i+1])
	{
		int temp = a[i];
		a[i] = a[i+1];
		a[i+1] = temp;
	}
}
__global__ void even(int *a,int len)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if( i % 2 == 0 && i < len - 1 && a[i] < a[i+1])
	{
		int temp = a[i];
		a[i] = a[i+1];
		a[i+1] = temp;
	}
}
void transpositionSort(int *a,int len)
{
	for(int i = 0;i < (len+1)/2;i++)
	{
		odd<<<ceil((float)len/256.0),256>>>(a,len);
		even<<<ceil((float)len/256.0),256>>>(a,len);
	}
}
int main()
{
	int n;
	printf("enter size of array: ");
	scanf("%d",&n);
	
	int input[n];
	int *d_input;
	int size = n * sizeof(int);
	
	printf("enter %d elements:\n",n);
	for(int i = 0;i < n;i++)
		scanf("%d",&input[i]);
	
	cudaMalloc((void**)&d_input,size);
	
	cudaMemcpy(d_input,input,size,cudaMemcpyHostToDevice);
	
	transpositionSort(d_input,n);
	
	cudaMemcpy(input,d_input,size,cudaMemcpyDeviceToHost);
	printf("result:\n");
	for(int i = 0;i < n;i++)
		printf("%d\t",input[i]);
	printf("\n");
	
	cudaFree(d_input);
	return 0;
}
