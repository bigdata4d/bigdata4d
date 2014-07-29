__global__ void compadd_kernel(float *a, float *b)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  int j = blockIdx.y*blockDim.y + threadIdx.y;
  int k = blockIdx.z;
  int ijk = i + j*100 + k * 100*100;

  a[ijk] += b[ijk];
}

void prepareCUDA(float **a_gpu, float **b_gpu, float *a, float *b)
{
  int size = 100*100*100*sizeof(float);

  cudaMalloc((void **)a_gpu, size);
  cudaMalloc((void **)a_gpu, size);

  cudaMemcpy(*a_gpu, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(*b_gpu, b, size, cudaMemcpyHostToDevice);
}

void testCUDA(float *a_gpu, float *b_gpu)
{
  dim3 grid(100,100,100);
  dim3 block(1,1,1);

  compadd_kernel<<<grid, block>>>(a_gpu, b_gpu);
}

void waitCUDA()
{
  cudaDeviceSynchronize();
}

void finishCUDA(float *a_gpu, float *b_gpu, float *a)
{
  int size = 100*100*100*sizeof(float);

  cudaMemcpy(a, a_gpu, size, cudaMemcpyDeviceToHost);

  cudaFree(a_gpu);
  cudaFree(b_gpu);
}
