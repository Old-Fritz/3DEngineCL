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
	VertexInputType* vertexData;
	int vertexCount;
	int vertexSize;
	grPrimitiveTopology topology;
} VertexBuffer;

typedef struct IndexBuffer
{
	unsigned int* indexData;
	int indexCount;
} IndexBuffer;


typedef struct ShaderObject
{
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	int primitiveCountEnd;
} ShaderObject;

typedef struct ShaderGlobal
{
	m3dVector3* outBuffer;
	float* depthBuffer;
	int* accessBuffer;
	int screenWidth, screenHegiht;
	float farZ, nearZ;
	float left, right, top, bottom;
} ShaderGlobal;

int VertexShader(VertexInputType* input, ShaderParams* params, PixelInputType* output);
int PixelShader(PixelInputType* input, ShaderParams* params, m3dVector4* outputColor);

ShaderGlobal* sg;

inline void getAccess(int ind)
{
	do {

	} while (atomic_cmpxchg(sg->accessBuffer + ind, 0, 1));
}

inline void giveAccess(int ind)
{
	atomic_xchg(sg->accessBuffer + ind, 0);
}

inline void draw(int ind, float z, m3dVector4* color)
{
	getAccess(ind);
	// if weren't any changes during computations save
	if (sg->depthBuffer[ind] == z)
		sg->outBuffer[ind] = *((m3dVector3*)color);
	giveAccess(ind);
}

int checkDepth(int ind, float z)
{
	float newZ = atomicMaxf(sg->depthBuffer + ind, z);
	if (newZ == z)
		return 1;
}