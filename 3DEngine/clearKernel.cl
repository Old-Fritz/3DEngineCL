__kernel void clearKernel(
	__global unsigned char* Buffer,
	__global float* values)
{
	//Get index into global data array
	int width = get_global_size(0);
	int count = get_global_size(2);
	int currentValueId = get_global_id(2);
	int bufferIndex = count*width*get_global_id(1) + count*get_global_id(0) + currentValueId;

	Buffer[bufferIndex] = values[currentValueId];
}