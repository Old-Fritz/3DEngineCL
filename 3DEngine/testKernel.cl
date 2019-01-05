struct rgb
{
	uchar r;
	uchar g;
	uchar b;
};


__kernel void testKernel(
	int x,
	int y,
	int r,
	__global unsigned char* pOutputVectorHost)
{
	//Get index into global data array
	float2 p1 = (float2)(get_global_id(0), get_global_id(1));
	float2 p2 = (float2)(x, y);
	int width = get_global_size(0);
	int height = get_global_size(1);
	int i;
	float k = 1;
	//struct rgb lrgb;

	//Check boundary conditions
	if (p1.x >= width || p1.y >= height) return;

	int ind = p1.y*width * 3 + p1.x * 3;

	if (fast_distance(p1, p2) > r)
	{
		//pOutputVectorHost[ind] = (uchar3)(255,0,0);
		pOutputVectorHost[ind] = 255;
		pOutputVectorHost[ind + 1] = 0;
		pOutputVectorHost[ind + 2] = 0;
	}
	else
	{
		//pOutputVectorHost[ind] = (uchar3)(255, 255, 255);
		pOutputVectorHost[ind] = 0;
		pOutputVectorHost[ind + 1] = 255;
		pOutputVectorHost[ind + 2] = 0;
	}


	//lrgb.g = (uchar)k;

	//pOutputVectorHost[ind] = lrgb;

	//Perform calculations
	//pOutputVectorHost[iJob] = MathCalculations(pInputVector1[iJob], pInputVector2[iJob]);
}