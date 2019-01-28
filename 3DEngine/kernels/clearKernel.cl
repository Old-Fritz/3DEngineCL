__kernel void clearKernel(
	__global unsigned char* Buffer,
	int bufferElementSize,
	float4 values)
{
	//Get index into global data array
	int width = get_global_size(0);
	int count = get_global_size(2);
	int currentValueId = get_global_id(2);
	int bufferIndex = count*width*get_global_id(1)
		+ count*get_global_id(0)
		+ currentValueId;

	if (bufferElementSize == 1)
	{
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
	else if (bufferElementSize == 4)
	{
		switch (currentValueId)
		{
		case 0:
			((__global float*)Buffer)[bufferIndex] = values.x;
			break;
		case 1:
			((__global float*)Buffer)[bufferIndex] = values.y;
			break;
		case 2:
			((__global float*)Buffer)[bufferIndex] = values.z;
			break;
		case 3:
			((__global float*)Buffer)[bufferIndex] = values.w;
			break;
		}
	}
	
}