#include <iostream>
#include <cuda.h>

using namespace std;

// ---------------- VECTOR ADDITION KERNEL ----------------

__global__ void vectorAdd(int *A, int *B, int *C) {

    int i = threadIdx.x;

    C[i] = A[i] + B[i];
}

// ---------------- MATRIX MULTIPLICATION KERNEL ----------------

__global__ void matrixMul(int A[2][2], int B[2][2], int C[2][2]) {

    int row = threadIdx.y;
    int col = threadIdx.x;

    C[row][col] = 0;

    for(int k = 0; k < 2; k++) {

        C[row][col] += A[row][k] * B[k][col];
    }
}

// ---------------- MAIN FUNCTION ----------------

int main() {

    // =====================================================
    // VECTOR ADDITION
    // =====================================================

    int size = 5;

    int h_A[] = {1, 2, 3, 4, 5};
    int h_B[] = {10, 20, 30, 40, 50};
    int h_C[size];

    int *d_A, *d_B, *d_C;

    // Allocate GPU memory
    cudaMalloc((void**)&d_A, size * sizeof(int));
    cudaMalloc((void**)&d_B, size * sizeof(int));
    cudaMalloc((void**)&d_C, size * sizeof(int));

    // Copy CPU to GPU
    cudaMemcpy(d_A, h_A, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size * sizeof(int), cudaMemcpyHostToDevice);

    // Kernel Launch
    vectorAdd<<<1, size>>>(d_A, d_B, d_C);

    // Copy GPU to CPU
    cudaMemcpy(h_C, d_C, size * sizeof(int), cudaMemcpyDeviceToHost);

    // Display Result
    cout << "Vector Addition:\n";

    for(int i = 0; i < size; i++) {

        cout << h_C[i] << " ";
    }

    cout << endl << endl;

    // Free vector memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // =====================================================
    // MATRIX MULTIPLICATION
    // =====================================================

    int h_M1[2][2] = {{1,2},{3,4}};
    int h_M2[2][2] = {{5,6},{7,8}};
    int h_M3[2][2];

    int (*d_M1)[2], (*d_M2)[2], (*d_M3)[2];

    // Allocate GPU memory
    cudaMalloc((void**)&d_M1, sizeof(h_M1));
    cudaMalloc((void**)&d_M2, sizeof(h_M2));
    cudaMalloc((void**)&d_M3, sizeof(h_M3));

    // Copy CPU to GPU
    cudaMemcpy(d_M1, h_M1, sizeof(h_M1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M2, h_M2, sizeof(h_M2), cudaMemcpyHostToDevice);

    // Thread configuration
    dim3 threads(2,2);

    // Kernel Launch
    matrixMul<<<1, threads>>>(d_M1, d_M2, d_M3);

    // Copy GPU to CPU
    cudaMemcpy(h_M3, d_M3, sizeof(h_M3), cudaMemcpyDeviceToHost);

    // Display Result
    cout << "Matrix Multiplication:\n";

    for(int i = 0; i < 2; i++) {

        for(int j = 0; j < 2; j++) {

            cout << h_M3[i][j] << " ";
        }

        cout << endl;
    }

    // Free matrix memory
    cudaFree(d_M1);
    cudaFree(d_M2);
    cudaFree(d_M3);

    return 0;
}
