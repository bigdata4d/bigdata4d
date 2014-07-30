#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <cstdio>
#include <cuda_runtime.h>
#include <cublas.h>

__global__ void compadd_kernel(float * __restrict__ a, float * __restrict__ b, int n)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  int j = blockIdx.y*blockDim.y + threadIdx.y;
  int k = blockIdx.z;

  if(i < 384 && j < 384 && k < 384)
  {
    int ijk = i + j*384 + k*384*384;
    a[ijk] += b[ijk];
  }
}

void waitCUDA()
{
  cudaDeviceSynchronize();
}

void prepareCUDA(float **a_gpu, float **b_gpu, float *a, float *b)
{
  int size = 384*384*384*sizeof(float);

  cudaMalloc((void **)a_gpu, size);
  cudaMalloc((void **)b_gpu, size);

  cudaMemcpy(*a_gpu, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(*b_gpu, b, size, cudaMemcpyHostToDevice);
}

void testCUDA(float *a_gpu, float *b_gpu)
{
  const int blocki = 256;
  const int blockj = 1;

  dim3 grid(384/blocki,384/blockj,384);
  dim3 block(blocki,blockj,1);

  compadd_kernel<<<grid, block>>>(a_gpu, b_gpu, 384);
}

void finishCUDA(float *a_gpu, float *b_gpu, float *a)
{
  int size = 384*384*384*sizeof(float);

  cudaMemcpy(a, a_gpu, size, cudaMemcpyDeviceToHost);

  cudaFree(a_gpu);
  cudaFree(b_gpu);
}

void testCUDA_thrust(thrust::device_vector<float> &a, const thrust::device_vector<float> &b)
{
  thrust::transform(b.begin(), b.end(), a.begin(), a.begin(), thrust::plus<float>());
}

void prepareCUDA_cublas(float **a_gpu, float **b_gpu, float *a, float *b)
{
  cublasInit();

  int size = 384*384*384*sizeof(float);

  cudaMalloc((void **)a_gpu, size);
  cudaMalloc((void **)b_gpu, size);

  cublasSetVector(384*384*384, sizeof(float), a, 1, *a_gpu, 1);
  cublasSetVector(384*384*384, sizeof(float), b, 1, *b_gpu, 1);
}

void testCUDA_cublas(float *a_gpu, float *b_gpu)
{
  cublasSaxpy(384*384*384, 1., b_gpu, 1, a_gpu, 1);
}

void finishCUDA_cublas(float *a_gpu, float *b_gpu, float *a)
{
  cublasGetVector(384*384*384, sizeof(float), a_gpu, 1, a, 1);
  cublasShutdown();

  cudaFree(a_gpu);
  cudaFree(b_gpu);
}
