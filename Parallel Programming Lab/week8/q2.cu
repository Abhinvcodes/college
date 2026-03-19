#include "cuda_runtime.h"
#include <stdio.h>

//solved 1D grid 1D block
__global__ void OneThreadPerRow(int *A, int *B, int *C, int m, int n, int k)
{
    int row = blockDim.x * blockIdx.x + threadIdx.x;

    if (row < m)
    {
        for (int j = 0; j < k; j++)  // for each column of C
        {
            int sum = 0;
            for (int t = 0; t < n; t++)  // dot product
            {
                sum += A[row * n + t] * B[t * k + j];
            }
            C[row * k + j] = sum;
        }
    }
}

//solved using 1D grid 1D block
__global__ void OneThreadPerColumn(int *A, int *B, int *C, int m, int n, int k)
{
    int col = blockDim.x * blockIdx.x + threadIdx.x;

    if (col < k)
    {
        for (int i = 0; i < m; i++)  // for each row
        {
            int sum = 0;
            for (int t = 0; t < n; t++)  // dot product
            {
                sum += A[i * n + t] * B[t * k + col];
            }
            C[i * k + col] = sum;
        }
    }
}
// solved using 1D grid 1D block
__global__ void OneThreadPerElement(int *A, int *B, int *C, int m, int n, int k)
{
    // Total number of elements in C is m * k
    int idx = blockDim.x * blockIdx.x + threadIdx.x;

    if (idx < m * k)
    {
        // Map 1D index to 2D row and column
        int row = idx / k;
        int col = idx % k;

        int sum = 0;
        for (int t = 0; t < n; t++) // Standard dot product loop
        {
            sum += A[row * n + t] * B[t * k + col];
        }
        C[idx] = sum;
    }
}

// Helper function to print matrix
void printMatrix(int* mat, int rows, int cols, const char* label) {
    printf("\nMatrix %s (%dx%d):\n", label, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", mat[i * cols + j]);
        }
        printf("\n");
    }
}

int main() {
    int m, n, k;
    printf("Enter dimensions (m, n, k): ");
    if (scanf("%d %d %d", &m, &n, &k) != 3) return -1;

    size_t sizeA = m * n * sizeof(int);
    size_t sizeB = n * k * sizeof(int);
    size_t sizeC = m * k * sizeof(int);

    int *h_A = (int*)malloc(sizeA);
    int *h_B = (int*)malloc(sizeB);
    int *h_C = (int*)malloc(sizeC);

    printf("Enter matrix A (%dx%d):\n", m, n);
    for (int i = 0; i < m * n; i++) scanf("%d", &h_A[i]);
    printf("Enter matrix B (%dx%d):\n", n, k);
    for (int i = 0; i < n * k; i++) scanf("%d", &h_B[i]);

    int *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, sizeA);
    cudaMalloc(&d_B, sizeB);
    cudaMalloc(&d_C, sizeC);

    cudaMemcpy(d_A, h_A, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, sizeB, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;

    // --- Launch 1: One Thread Per Row ---
    int blocksPerRow = (m + threadsPerBlock - 1) / threadsPerBlock;
    OneThreadPerRow<<<blocksPerRow, threadsPerBlock>>>(d_A, d_B, d_C, m, n, k);
    
    // Copy and Print
    cudaMemcpy(h_C, d_C, sizeC, cudaMemcpyDeviceToHost);
    printMatrix(h_C, m, k, "Result (OneThreadPerRow)");

    // --- Launch 2: One Thread Per Column ---
    int blocksPerCol = (k + threadsPerBlock - 1) / threadsPerBlock;
    OneThreadPerColumn<<<blocksPerCol, threadsPerBlock>>>(d_A, d_B, d_C, m, n, k);
    
    // Copy and Print
    cudaMemcpy(h_C, d_C, sizeC, cudaMemcpyDeviceToHost);
    printMatrix(h_C, m, k, "Result (OneThreadPerColumn)");

    // --- Launch 3: One Thread Per Element ---
    int blocksPerElem = (m * k + threadsPerBlock - 1) / threadsPerBlock;
    OneThreadPerElement<<<blocksPerElem, threadsPerBlock>>>(d_A, d_B, d_C, m, n, k);

    // Copy and Print
    cudaMemcpy(h_C, d_C, sizeC, cudaMemcpyDeviceToHost);
    printMatrix(h_C, m, k, "Result (OneThreadPerElement)");

    // Cleanup
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    free(h_A); free(h_B); free(h_C);

    return 0;
}
