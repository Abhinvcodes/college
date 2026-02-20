#include "cuda_runtime.h"
#include <stdio.h>

__global__ void convolution(int *a,int *m,int *r,int al, int ml)
{
	
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < al)
	{
		int start_point = idx - ml / 2;
		int sum=0;
		for(int i=0;i<ml;i++)
		{
			if(start_point + i >= 0 && start_point + i < al)
				sum += a[start_point+i] * m[i];
		}
		r[idx] = sum;
	}
}

int main()
{
	int width,mask_width;
	printf("enter length of array\n");
	scanf("%d",&width);
	printf("enter length of mask array\n");
	scanf("%d",&mask_width);
	
	int array[width],mask[mask_width],result[width];
	int *d_array,*d_mask,*d_result;
	int size1 = width * sizeof(int);
	int size2 = mask_width * sizeof(int);
	
	printf("enter %d elements:\n",width);
	for(int i = 0;i < width;i++)
		scanf("%d",&array[i]);
	printf("enter %d elements for mask:\n",mask_width);
	for(int i = 0;i < mask_width;i++)
		scanf("%d",&mask[i]);	
	
	cudaMalloc((void**)&d_array, size1);
	cudaMalloc((void**)&d_mask, size2);
	cudaMalloc((void**)&d_result, size1);
	
	cudaMemcpy(d_array,array,size1,cudaMemcpyHostToDevice);
	cudaMemcpy(d_mask,mask,size2,cudaMemcpyHostToDevice);
	
	convolution<<<ceil((float)width/256.0),256>>>(d_array,d_mask,d_result,width,mask_width);
	
	cudaMemcpy(result,d_result,size1,cudaMemcpyDeviceToHost);
	
	printf("result:\n");
	for(int i = 0;i < width;i++)
		printf("%d\t",result[i]);
	printf("\n");
	
	cudaFree(d_array);
	cudaFree(d_mask);
	cudaFree(d_result);
	
	return 0;
}
