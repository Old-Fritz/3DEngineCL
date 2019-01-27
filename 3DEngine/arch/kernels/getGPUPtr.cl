__kernel void getGPUPtrKernel(
	__global unsigned int* sourceBuffer,
	__global unsigned int* destBuffer)
{
	destBuffer[0] = sourceBuffer;
}