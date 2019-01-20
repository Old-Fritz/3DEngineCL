
typedef struct VertexInputType VertexInputType;
typedef struct PixelInputType PixelInputType;
typedef struct ShaderParams ShaderParams;

typedef enum grPrimitiveTopology {
	GR_PRIMITIVE_TOPOLOGY_POINT = 1,
	GR_PRIMITIVE_TOPOLOGY_LINE = 2,
	GR_PRIMITIVE_TOPOLOGY_TRIANGLE = 3
} grPrimitiveTopology;

typedef struct VertexBuffer
{
	__global VertexInputType* vertexData;
	int vertexCount;
	int vertexSize;
	grPrimitiveTopology topology;
} VertexBuffer;

typedef struct IndexBuffer
{
	__global unsigned int* indexData;
	int indexCount;
} IndexBuffer;


typedef struct ShaderObject
{
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	int primitiveCountEnd;
} ShaderObject;

typedef struct ShaderGlobal
{
	__global m3dVector3* outBuffer;
	__global float* depthBuffer;
	__global int* accessBuffer;
	int screenWidth, screenHegiht;
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

inline void draw(int ind, float z, m3dVector4* color, __global ShaderGlobal* sg)
{
	getAccess(ind, sg);
	// if weren't any changes during computations save
	if (sg->depthBuffer[ind] == z)
		sg->outBuffer[ind] = *((m3dVector3*)color);
	giveAccess(ind, sg);
}

int checkDepth(int ind, float z, __global ShaderGlobal* sg)
{
	float newZ = atomicMaxf(sg->depthBuffer + ind, z);
	if (newZ == z)
		return 1;
}