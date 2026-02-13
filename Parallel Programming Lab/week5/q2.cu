#include "cuda_runtime.h"
#include <stdio.h>
#include <math.h>
__global__ void add(int *a,int *b,int *c,int n){
	int i = blockDim.x*blockIdx.x + threadIdx.x;
	if(i < n)
		c[i] = a[i]+b[i];
}

int main(){
	int n;
	printf("enter size:\n");
	scanf("%d",&n);
	int size = n * sizeof(int);
	int a[n],b[n],c[n];
	int *d_a,*d_b,*d_c;
	
	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	cudaMalloc((void**)&d_c,size);
	
	printf("enter %d elements for a\n",n);
	for(int i = 0;i < n;i++)
		scanf("%d",&a[i]);
	
	printf("enter %d elements for b\n",n);
	for(int i = 0;i < n;i++)
		scanf("%d",&b[i]);
	
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	
	add<<<ceil(n/256.0),256>>>(d_a,d_b,d_c,n);
	
	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	printf("result\n");
	for(int i = 0;i< n;i++)
		printf("%d ",c[i]);
	printf("\n");
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
