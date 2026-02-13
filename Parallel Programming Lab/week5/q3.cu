#include "cuda_runtime.h"
#include <stdio.h>

__global__ void convertToSine(float *angles,float *sines,int n){
	int i = blockDim.x*blockIdx.x+threadIdx.x;
	if(i<n)
		sines[i]=sinf(angles[i]);
}

int main(){
	int n;
	printf("enter n\n");
	scanf("%d",&n);
	float angles[n],sines[n];
	float *d_angles,*d_sines;
	int size = n * sizeof(float);
	
	cudaMalloc((void**)&d_sines,size);
	cudaMalloc((void**)&d_angles,size);
	
	printf("enter %d angles in radians\n",n);
	for(int i = 0;i < n;i++)
		scanf("%f",&angles[i]);
		
	cudaMemcpy(d_angles,angles,size,cudaMemcpyHostToDevice);
	
	convertToSine<<<1,n>>>(d_angles,d_sines,n);
	cudaMemcpy(sines,d_sines,size,cudaMemcpyDeviceToHost);
	printf("sines of the angles\n");
	for(int i = 0;i < n;i++)
		printf("%f ",sines[i]);
	printf("\n");
	cudaFree(d_angles);
	cudaFree(d_sines);
	return 0;
}
