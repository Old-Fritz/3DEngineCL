__kernel void clearKernel(
	__global unsigned char* Buffer,
	int bufferElementSize,
	float4 values)
{
	//Get index into global data array
	int width = get_global_size(0);
	int count = get_global_size(2);
	int currentValueId = get_global_id(2);
	int bufferIndex = bufferElementSize*count*width*get_global_id(1)
		+ bufferElementSize*count*get_global_id(0)
		+ bufferElementSize*currentValueId;

	switch (currentValueId)
	{
	case 0:
		Buffer[bufferIndex] = values.x;
		break;
	case 1:
		Buffer[bufferIndex] = values.y;
		break;
	case 2:
		Buffer[bufferIndex] = values.z;
		break;
	case 3:
		Buffer[bufferIndex] = values.w;
		break;
	}
	
}