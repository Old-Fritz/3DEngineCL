
inline float atomicMaxf(volatile __global float *source, const float operand) {
	union {
		unsigned int intVal;
		float floatVal;
	} newVal;
	union {
		unsigned int intVal;
		float floatVal;
	} prevVal;
	do {
		prevVal.floatVal = *source;
		newVal.floatVal = max(prevVal.floatVal, operand);
	} while (atomic_cmpxchg((volatile __global unsigned int *)source, prevVal.intVal, newVal.intVal) != prevVal.intVal);

	return newVal.floatVal;
}

void swap(void** val1, void** val2)
{
	void* temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}





typedef struct VertexInputType VertexInputType;
typedef struct PixelInputType PixelInputType;
typedef struct ShaderParams ShaderParams;

typedef struct rgb
{
	uchar b;
	uchar g;
	uchar r;
} rgb;


typedef enum grPrimitiveTopology {
	GR_PRIMITIVE_TOPOLOGY_POINT = 1,
	GR_PRIMITIVE_TOPOLOGY_LINE = 2,
	GR_PRIMITIVE_TOPOLOGY_TRIANGLE = 3
} grPrimitiveTopology;


typedef struct ShaderObject
{
	__global VertexInputType* vertexData;
	__global unsigned int* indexData;
	grPrimitiveTopology topology;
	int primitiveCountEnd;
} ShaderObject;

typedef struct ShaderGlobal
{
	__global rgb* outBuffer;
	__global float* depthBuffer;
	__global int* accessBuffer;
	int screenWidth, screenHeight;
	float farZ, nearZ;
	float left, right, top, bottom;
} ShaderGlobal;

int VertexShader(VertexInputType* input, ShaderParams* params, PixelInputType* output);
int PixelShader(PixelInputType* input, ShaderParams* params, m3dVector4* outputColor);


inline void getAccess(int ind, __global ShaderGlobal* sg)
{
	do {

	} while (atomic_cmpxchg(sg->accessBuffer + ind, 0, 1));
}

inline void giveAccess(int ind, __global ShaderGlobal* sg)
{
	atomic_xchg(sg->accessBuffer + ind, 0);
}

int checkDepth(int ind, float z, __global ShaderGlobal* sg)
{
	float newZ = atomicMaxf(sg->depthBuffer + ind, z);
	if (newZ == z)
		return 1;

	return 0;
}

inline void draw(int ind, float z, m3dVector4* color, __global ShaderGlobal* sg)
{
	rgb newColor;
	__global char* value = sg->outBuffer + ind;
	newColor.r = color->x;
	newColor.g = color->y;
	newColor.b = color->z;
	//barrier(CLK_GLOBAL_MEM_FENCE);
	if (checkDepth(ind, 1/z, sg))
	{
		sg->outBuffer[ind] = newColor;
		//atomic_xchg((__global int*)(value), (int)newColor.b);
		//atomic_xchg((__global int*)(value+1), (int)newColor.g);
		//atomic_xchg((__global int*)(value+2), (int)newColor.r);
	}
	//barrier(CLK_GLOBAL_MEM_FENCE);
}




