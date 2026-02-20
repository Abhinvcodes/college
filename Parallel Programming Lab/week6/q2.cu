#include "cuda_runtime.h"
#include <stdio.h>

__global__ void selSort(int *arr,int len, int *res)
{
	int i = blockIdx.x *blockDim.x + threadIdx.x;
	if(i<len)
	{
		int idx=0;
		int chosen_element = arr[i];
		for(int j = 0;j < len;j++)
		{
			if((chosen_element > arr[j]) || (chosen_element == arr[j] && j<i))
				idx++; 
		}
		res[idx] = chosen_element;
	}
}
int main()
{
	int n;
	printf("enter length of array:\n");
	scanf("%d",&n);
	
	int array[n],result[n];
	int *d_array,*d_result;
	int size = n * sizeof(int);
	
	printf("enter %d values:\n",n);
	for(int i = 0;i < n;i++)
		scanf("%d",&array[i]);
	
	cudaMalloc((void**)&d_array,size);
	cudaMalloc((void**)&d_result,size);
	
	cudaMemcpy(d_array,array,size,cudaMemcpyHostToDevice);
	
	selSort<<<ceil((float)n/256.0),256>>>(d_array,n,d_result);
	
	cudaMemcpy(result,d_result,size,cudaMemcpyDeviceToHost);
	printf("result:\n");
	for(int i = 0;i < n;i++)
		printf("%d\t",result[i]);
	printf("\n");
	
	cudaFree(d_array);
	cudaFree(d_result);
	return 0;
}
