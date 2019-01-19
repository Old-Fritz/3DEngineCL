#include"../libs/math3d.cl"

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

m3dVector3* gOutBuffer;
float* gDepthBuffer;
int* gAccessBuffer;
int gScreenWidth, gScreenHegiht;
float gFarZ, gNearZ;
float gLeft, gRight, gTop, gBottom;
int VertexShader(VertexInputType* input, ShaderParams* params, PixelInputType* output);
int PixelShader(PixelInputType* input, ShaderParams* params, m3dVector4* outputColor);

inline void getAccess(int ind)
{
	do {

	} while (atomic_cmpxchg(gAccessBuffer + ind, 0, 1));
}

inline void giveAccess(int ind)
{
	atomic_xchg(gAccessBuffer + ind, 0);
}

inline void draw(int ind, float z, m3dVector4* color)
{
	getAccess(ind);
	// if weren't any changes during computations save
	if(gDepthBuffer[ind]==z)
		gOutBuffer[ind] = *((m3dVector3*)color);
	giveAccess(ind);
}

int checkDepth(int ind, float z)
{
	float newZ = atomicMaxf(gDepthBuffer + ind, z);
	if (newZ == z)
		return 1;
}


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

float interpolateF(float value1, float value2, float perCent)
{
	return value1 + (value2 - value1)*perCent;
}

void interpolatePI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue, float perCent)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = interpolateF(lValueArray[i], rValueArray[i], perCent);
}
void createDeltaPI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue, float steps)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = (rValueArray[i] - lValueArray[i])/steps;
}
void addPI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = lValueArray[i] + rValueArray[i];
}
void subPI(PixelInputType* output, PixelInputType* lValue, PixelInputType* rValue)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *lValueArray, *rValueArray;
	outputArray = output;
	lValueArray = lValue;
	rValueArray = rValue;
	for (i = 0;i < size;i++)
		outputArray[i] = lValueArray[i] - rValueArray[i];
}
void copyPI(PixelInputType* output, PixelInputType* value)
{
	int i;
	int size = sizeof(PixelInputType) / sizeof(float);
	float *outputArray, *valueArray;
	outputArray = output;
	valueArray = value;
	for (i = 0;i < size;i++)
		outputArray[i] = valueArray[i];
}


void processPoint(PixelInputType* input, int x, int y, float z, ShaderParams* params)
{
	int ind, result;
	float z;
	m3dVector4 color;
	ind = gScreenWidth*y + x; // ind in buffer

	// check screen
	if (x < gLeft || x> gRight || y < gBottom || y>gTop)
		return;

	// check depth buffer
	if (!checkDepth(x, y, z))
		return;

	// proccess shader
	result = PixelShader(input, params, &color);
	if (!result)
		return;

	// draw pixel
	draw(ind, z, &color);
}

void rasterizer1(PixelInputType* input, ShaderParams* params)
{
	m3dVector3* position = input;
	// there are only one point so we can only draw it immidietly
	processPoint(input, position->x, position->y, position->z, params);
}

void rasterizer2(PixelInputType* input1, PixelInputType* input2, ShaderParams* params)
{
	m3dVector3 *pos1, *pos2, *pos;
	PixelInputType stepInput;
	PixelInputType nextInput;
	float slope;
	int steps;
	int x, y, i;
	pos1 = input1;
	pos2 = input2;
	slope = (pos2->x - pos1->x) / (pos2->y - pos2->y);
	// if line closer to horizontal
	if (slope > -1 && slope < 1)
	{
		// go from left to right
		if (pos1->x > pos2->x)
		{
			swap(&input2, &input1);
			swap(&pos2, &pos1);
		}
		steps = pos2->x - pos1->x;
	}
	else
	{
		// go from bottom to up
		if (pos1->y > pos2->y)
		{
			swap(&input2, &input1);
			swap(&pos2, &pos1);
		}
		steps = pos2->y - pos1->y;
	}
	copyPI(&nextInput, input1);
	createDeltaPI(&stepInput, input1, input2, steps);
	for (i = 0;i < steps;i++)
	{
		pos = &nextInput;
		processPoint(&nextInput, pos->x, pos->y, pos->z,params);
		addPI(&nextInput, &nextInput, &stepInput);
	}
}

void rasterizer3(PixelInputType* input1, PixelInputType* input2, PixelInputType* input3, ShaderParams* params)
{
	m3dVector3 *pos1, *pos2, *pos3, *pos;
	PixelInputType stepInput1, stepInput2, stepInput3;
	PixelInputType nextInputL, nextInputR;
	int steps, i;
	// order verticies py1<py2<py3
	pos1 = input1;
	pos2 = input2;
	pos3 = input3;
	if (pos2->y < pos1->y)
	{
		swap(&input2, &input1);
		swap(&pos2, &pos1);
	}
	if (pos3->y < pos1->y)
	{
		swap(&input3, &input1);
		swap(&pos3, &pos1);
	}
	if (pos3->y < pos2->y)
	{
		swap(&input3, &input2);
		swap(&pos3, &pos2);
	}
	steps = pos3->y - pos1->y;
	createDeltaPI(&stepInput1, input1, input3, steps);
	createDeltaPI(&stepInput2, input1, input2, (pos3->y - pos1->y) / steps*(pos2->y - pos1->y));
	createDeltaPI(&stepInput3, input2, input3, (pos3->y - pos1->y) / steps*(pos3->y - pos2->y));
	copyPI(&nextInputL, &input1);
	copyPI(&nextInputR, &input1);

	// bottom side
	while (((m3dVector3*)&nextInputL)->y <= pos2->y)
	{
		rasterizer2(&nextInputL, &nextInputR, params);
		addPI(&nextInputL, &nextInputL, &stepInput1);
		addPI(&nextInputR, &nextInputR, &stepInput2);
	}
	// up side
	copyPI(&nextInputL, &input3);
	copyPI(&nextInputR, &input3);
	while (((m3dVector3*)&nextInputL)->y > pos2->y)
	{
		rasterizer2(&nextInputL, &nextInputR, params);
		subPI(&nextInputL, &nextInputL, &stepInput1);
		subPI(&nextInputR, &nextInputR, &stepInput3);
	}
}



void spliter2D1(PixelInputType* psInput, ShaderParams* params)
{
	// There can be 2D splitters
	// ...
	// ...
	rasterizer1(psInput, params);
}

void spliter2D2(PixelInputType* psInput1, PixelInputType* psInput2, ShaderParams* params)
{
	// There can be 2D splitters
	// ...
	// ...
	rasterizer2(psInput1, psInput2, params);
}

void spliter2D3(PixelInputType* psInput1, PixelInputType* psInput2, PixelInputType* psInput3, ShaderParams* params)
{
	// There can be 2D splitters
	// ...
	// ...
	rasterizer3(psInput1, psInput2, psInput2, params);
}


void spliter1(VertexInputType* vsInput, ShaderParams* params)
{
	int result;
	PixelInputType psInput;
	m3dVector3* position = vsInput; // first value is position
	float coordZ = position->z;

	// Finish if point out of z planes
	if (coordZ < gNearZ || coordZ > gFarZ)
		return;

	// Calculate vertex shader that can stop execution
	result = VertexShader(vsInput, params, &psInput);
	if (!result)
		return;

	// save z coord
	position = &psInput;
	position->z = coordZ;

	// split in 2D and go next
	spliter2D1(&psInput, params);
}

void spliter2(VertexInputType* vsInput1, VertexInputType* vsInput2, ShaderParams* params)
{
	int result;
	PixelInputType psInput1, psInput2;
	m3dVector3 *pos1, *pos2;
	float z1, z2;
	pos1 = vsInput1; // first value is position
	pos2 = vsInput2;
	z1 = pos1->z;
	z2 = pos2->z;

	// Finish if both points out of near Z
	if (pos1->z < gNearZ && pos2->z < gNearZ)
		return;

	// Separate line if it cross near Z plane
	if (pos1->z < gNearZ || pos2->z < gNearZ)
	{
		float cutPercent;
		// swap so P1 is out of plane
		if (pos2->z < gNearZ)
		{
			swap(&vsInput1, &vsInput2);
			swap(&pos1, &pos2);
		}
		cutPercent = (gNearZ - pos1->z) / (pos2->z - pos1->z);
		interpolatePI(vsInput1, vsInput1, vsInput2, cutPercent);
		z1 = gNearZ;
		z2 = pos2->z;
	}

	// Calculate vertex shader that can stop execution
	result = VertexShader(vsInput1, params, &psInput1);
	if (!result)
		return;

	result = VertexShader(vsInput2, params, &psInput2);
	if (!result)
		return;

	// save z coord
	pos1 = &psInput1;
	pos2 = &psInput2;
	pos1->z = z1;
	pos2->z = z2;

	// split in 2D and go next
	spliter2D2(&psInput1, &psInput2, params);
}

void spliter3(VertexInputType* vsInput1, VertexInputType* vsInput2, VertexInputType* vsInput3, ShaderParams* params)
{
	int result;
	VertexInputType vsInput4;
	PixelInputType psInput1, psInput2, psInput3, psInput4;
	m3dVector3 *pos1, *pos2, *pos3, *pos4;
	pos4 = 0;
	float z1, z2, z3, z4;
	pos1 = vsInput1; // first value is position
	pos2 = vsInput2;
	pos3 = vsInput3;
	z1 = pos1->z;
	z2 = pos2->z;
	z3 = pos3->z;

	// Finish if all points out of near Z
	if (pos1->z < gNearZ && pos2->z < gNearZ && pos3->z < gNearZ);
	return;

	// Separate bottom part of triangle if it cross near Z plane
	// if two points out of plane
	if ((pos1->z < gNearZ && pos2->z < gNearZ) || 
		(pos1->z < gNearZ && pos3->z < gNearZ) || 
		(pos2->z < gNearZ && pos3->z < gNearZ))
	{
		float cutPercent1, cutPercent2;
		// swap so P1 is in plane
		if (pos2->z >= gNearZ)
		{
			swap(&vsInput1, &vsInput2);
			swap(&pos1, &pos2);
		}
		if (pos3->z >= gNearZ)
		{
			swap(&vsInput1, &vsInput3);
			swap(&pos1, &pos3);
		}

		cutPercent1 = (gNearZ - pos2->z) / (pos1->z - pos2->z);
		cutPercent2 = (gNearZ - pos3->z) / (pos1->z - pos3->z);
		interpolatePI(vsInput2, vsInput2, vsInput1, cutPercent1);
		interpolatePI(vsInput3, vsInput3, vsInput1, cutPercent2);
		z1 = pos1->z;
		z2 = gNearZ;
		z3 = gNearZ;
	}
	// only one point out of plane
	else if (pos1->z < gNearZ || pos2->z < gNearZ || pos3->z < gNearZ)
	{
		float cutPercent1, cutPercent2;


		// swap so P1 is out of plane
		if (pos2->z < gNearZ)
		{
			swap(&vsInput1, &vsInput2);
			swap(&pos1, &pos2);
		}
		if (pos3->z < gNearZ)
		{
			swap(&vsInput1, &vsInput3);
			swap(&pos1, &pos3);
		}

		cutPercent1 = (gNearZ - pos1->z) / (pos2->z - pos1->z);
		cutPercent2 = (gNearZ - pos1->z) / (pos2->z - pos1->z);
		interpolatePI(vsInput1, vsInput1, vsInput2, cutPercent1);
		interpolatePI(&vsInput4, vsInput1, vsInput3, cutPercent2);
		pos4 = &vsInput4;
		z1 = gNearZ;
		z2 = pos2->z;
		z3 = pos2->z;
		z4 = gNearZ;
	}

	
	
	// Calculate vertex shader that can stop execution
	result = VertexShader(vsInput1, params, &psInput1);
	if (!result)
		return;

	result = VertexShader(vsInput2, params, &psInput2);
	if (!result)
		return;

	result = VertexShader(vsInput3, params, &psInput3);
	if (!result)
		return;

	// save z coord
	pos1 = &psInput1;
	pos2 = &psInput2;
	pos3 = &psInput3;
	pos1->z = z1;
	pos2->z = z2;
	pos3->z = z3;

	// check if trianle has been  splitted on two parts
	if (pos4 != 0)
	{
		// Calculate vertex shader that can stop execution
		result = VertexShader(&vsInput4, params, &psInput4);
		if (!result)
			return;

		pos4 = &psInput4;
		pos4->z = z4;

		// split in 2D and go next
		spliter2D3(&psInput2, &psInput3, &psInput4, params);
	}

	// split in 2D and go next
	spliter2D3(&psInput2, &psInput3, &psInput4, params);
}



void primitiveController1(ShaderObject* object, ShaderParams* params, int primitiveId)
{
	int ind;
	VertexInputType* vsInput;

	// getIndex of current primitive
	ind = object->indexBuffer->indexData[primitiveId]; 
	// get vertex with given index
	vsInput = object->vertexBuffer->vertexData + ind;
	
	// go to rasterize stage
	rasterizer1(VertexShader(vsInput, params), params);
}

void primitiveController2(ShaderObject* object, ShaderParams* params, int primitiveId)
{
	int ind1, ind2;
	VertexInputType *vsInput1, *vsInput2;

	// getIndex of current primitive
	ind1 = object->indexBuffer->indexData[primitiveId * 2];
	ind2 = object->indexBuffer->indexData[primitiveId * 2 + 1];

	// get vertex with given index
	vsInput1 = object->vertexBuffer->vertexData + ind1;
	vsInput2 = object->vertexBuffer->vertexData + ind2;

	// go to rasterize stage
	rasterizer2(VertexShader(vsInput1, params), VertexShader(vsInput2, params), params);
}

void primitiveController3(ShaderObject* object, ShaderParams* params, int primitiveId)
{
	int ind1, ind2, ind3;
	VertexInputType *vsInput1, *vsInput2, *vsInput3;

	// getIndex of current primitive
	ind1 = object->indexBuffer->indexData[primitiveId * 3];
	ind2 = object->indexBuffer->indexData[primitiveId * 3 + 1];
	ind3 = object->indexBuffer->indexData[primitiveId * 3 + 2];

	// get vertex with given index
	vsInput1 = object->vertexBuffer->vertexData + ind1;
	vsInput2 = object->vertexBuffer->vertexData + ind2;
	vsInput2 = object->vertexBuffer->vertexData + ind3;

	// go to rasterize stage
	rasterizer3(VertexShader(vsInput1, params), VertexShader(vsInput2, params), VertexShader(vsInput3, params), params);
}

void getObjectId(ShaderObject* objects, int primitiveId, int objectsCount, int* objectId, int* relativeId)
{
	int i;
	for (i = 0;i <= objectsCount;i++)
	{
		if (objects[i].primitiveCountEnd>=primitiveId)
		{
			*objectId = i;
			if (i > 0)
				*relativeId = primitiveId - objects[i - 1].primitiveCountEnd - 1;
			else
				*relativeId = primitiveId;
		}
	}
}

void shaderKernel(ShaderObject* objects, ShaderParams* params, long objectsCount)
{
	int objectId, relativeId;
	getObjectId(objects, get_global_id(0), objectsCount, &objectId, &relativeId);
}