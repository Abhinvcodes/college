#include "cuda_runtime.h"
#include <stdio.h>

__global__ void add(int *a, int *b, int *c,int n)
{
	int i = blockDim.x*blockIdx.x + threadIdx.x;
	if(i < n)
		c[i] = a[i]+b[i];
}

int main()
{
	int n;
	printf("enter size:\n");
	scanf("%d",&n);
	int size = n * sizeof(int);
	int a[n],b[n],c[n];
	int *d_a,*d_b,*d_c;

	//allocate mem for a,b,c on device
	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_c,size);	
	
	//input a,b
	printf("enter %d values for a:\n",n);
	for(int i = 0;i < n;i++)
		scanf("%d",&a[i]);
	printf("enter %d values for b:\n",n);
	for(int i = 0;i < n;i++)
		scanf("%d",&b[i]);

	//copy values to device memory
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	
	add<<<n,1 >>>(d_a,d_b,d_c,n);
	printf("c using %d blocks and 1 thread\n",n);
	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	for(int i=0;i<n;i++)
		printf("%d ",c[i]);

	printf("\nc using 1 block and %d threads\n",n);
	add<<<1,n >>>(d_a,d_b,d_c,n);
	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	for(int i=0;i<n;i++)
		printf("%d ",c[i]);
	printf("\n");
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
