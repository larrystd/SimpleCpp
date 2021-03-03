#include <stdio.h>
#include <cuda_runtime.h> 
#include <iostream>
#include <chrono>
#include <cstdlib>
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

__global__ void saxpy_par(int n, float a, float *x, float *y)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) y[i] = a*x[i] + y[i];
}

float saxpy_check(int n, float a, float *x, float *y, float *z, int niter)
{
// a, x, y == original data for saxpy
// z = result found -- with which to compare.
    float s=0.0, t = 0.0;
    for (int i=0; i<n; i++) {
        for (int j = 0; j < niter; j++)     // loop NITER in cpu
            y[i] += a * x[i] ;
        s += (y[i] - z[i])*(y[i] - z[i]);   // loss
        t += z[i]*z[i];
    }
    if (t == 0.0) return(-1);
    else
        return(sqrt(s/t));    // rate of loss
}

int main(void)
{
  int N = 1<<23;
  float a = 2.0f;
  float *x, *y,*z, *d_x, *d_y;
  x = (float*)malloc(N*sizeof(float));
  y = (float*)malloc(N*sizeof(float));
  z = (float*)malloc(N*sizeof(float));
  cudaMalloc(&d_x, N*sizeof(float)); 
  cudaMalloc(&d_y, N*sizeof(float));

  for (int i = 0; i < N; i++) {
    x[i] = rand();
    y[i] = rand();
  }
  int NITER = 100;

  
  for (int vecLen = 2048; vecLen <= N; vecLen*=2){
    long opNum =256*((vecLen + 255) / 256)*2;   // operator num, 256*((vecLen + 255) / 256) threads and one thread with two operators
    cudaMemcpy(d_x, x, vecLen*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, vecLen*sizeof(float), cudaMemcpyHostToDevice);
    
    high_resolution_clock::time_point beginTime = high_resolution_clock::now();
    for (int iter = 0 ;iter<NITER; iter++){
    // data transfers included in timing       
    // Perform SAXPY on 1M elements
        saxpy_par<<<(vecLen+255)/256, 256>>>(vecLen, a, d_x, d_y);  // loop NITER
    }
    high_resolution_clock::time_point endTime = high_resolution_clock::now();   // end time
    cudaMemcpy(z, d_y, vecLen*sizeof(float), cudaMemcpyDeviceToHost);   //  copy data from gpu to cpu
    microseconds timeInterval = std::chrono::duration_cast<microseconds>(endTime - beginTime);  // Time difference,unit is microseconds
    double time2 = timeInterval.count();  
    time2 /= NITER;
    double MFLOPS = opNum/time2;    // MFLOPS, one second number of operators
    double error = saxpy_check(vecLen, a, x, y, z, NITER);   // check
    printf("vecLen = %ld, Mflops = %f, Error = %f\n", vecLen,MFLOPS, error);
  }
  cudaFree(d_x);
  cudaFree(d_y);
  free(x);
  free(y);
  free(z);
}