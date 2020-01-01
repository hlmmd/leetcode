# cuda 编程

并行计算

核函数：在GPU设备上执行的函数

```cpp
__global__ void kernel() {}

__device__

```

cudaMalloc、cudaMemcpy、cudaMemcpyDeviceToHost、cudaMemcpyHostToDevice、cudaFree

核函数第一个参数： 线程块个数, blockIdx.x 不超过65535

第二个参数： 线程数量 threadIdx.x，不超过maxThreadsPerBlock，目前大多数为512

gridDim.x：线程格中线程块的数量。

blockDim.x：线程块中每一维的线程数量。

tid = threadIdx.x + blockIdx.x * blockDim.x

tid += blockDim.x * gridDim.x

共享内存

一个线程块中的多个线程能够共享内存

```cpp
__share__
```

__syncthreads() :用于同步，确保每个线程都执行了__syncthreads()之后才会继续执行。

线程发散

不要将__syncthreads()调用写到if语句中，否则可能会循环等待。


