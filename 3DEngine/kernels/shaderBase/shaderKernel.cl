

void primitiveController1(__global ShaderObject* object, ShaderParams* params, int primitiveId, __global ShaderGlobal* sg)
{
	int result, ind;
	PixelInputType psInput;
	VertexInputType vsInput;

	// getIndex of current primitive
	ind = object->indexBuffer.indexData[primitiveId];
	// get vertex with given index
	vsInput = object->vertexBuffer.vertexData[ind];

	// Calculate vertex shader that can stop execution
	result = VertexShader(&vsInput, params, &psInput);
	if (!result)
		return;
	
	// go to splitter stage
	spliter1(&psInput, params, sg);
}
void primitiveController2(__global ShaderObject* object, ShaderParams* params, int primitiveId, __global ShaderGlobal* sg)
{
	int result, ind1, ind2;
	PixelInputType psInput1, psInput2;
	VertexInputType vsInput1, vsInput2;

	// getIndex of current primitive
	ind1 = object->indexBuffer.indexData[primitiveId * 2];
	ind2 = object->indexBuffer.indexData[primitiveId * 2 + 1];

	// get vertex with given index
	vsInput1 = object->vertexBuffer.vertexData[ind1];
	vsInput2 = object->vertexBuffer.vertexData[ind2];

	// Calculate vertex shader that can stop execution
	result = VertexShader(&vsInput1, params, &psInput1);
	if (!result)
		return;

	result = VertexShader(&vsInput2, params, &psInput2);
	if (!result)
		return;

	// go to splitter stage
	spliter2 (&psInput1, &psInput2, params, sg);
}
void primitiveController3(__global ShaderObject* object, ShaderParams* params, int primitiveId, __global ShaderGlobal* sg)
{
	int result, ind1, ind2, ind3;
	PixelInputType psInput1, psInput2, psInput3;
	VertexInputType vsInput1, vsInput2, vsInput3;

	// getIndex of current primitive
	ind1 = object->indexBuffer.indexData[primitiveId * 3];
	ind2 = object->indexBuffer.indexData[primitiveId * 3 + 1];
	ind3 = object->indexBuffer.indexData[primitiveId * 3 + 2];

	// get vertex with given index
	vsInput1 = object->vertexBuffer.vertexData[ind1];
	vsInput2 = object->vertexBuffer.vertexData[ind2];
	vsInput3 = object->vertexBuffer.vertexData[ind3];

	// Calculate vertex shader that can stop execution
	result = VertexShader(&vsInput1, params, &psInput1);
	if (!result)
		return;

	result = VertexShader(&vsInput2, params, &psInput2);
	if (!result)
		return;

	result = VertexShader(&vsInput3, params, &psInput3);
	if (!result)
		return;

	// go to splitter stage
	spliter3(&psInput1, &psInput2, &psInput3, params, sg);
}



void getObjectId(__global ShaderObject* objects, int primitiveId, int objectsCount, int* objectId, int* relativeId)
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

__kernel void shaderKernel(__global ShaderObject* objects, __global ShaderParams* params, int objectsCount, __global ShaderGlobal* shaderGlobal)
{
	int objectId, relativeId;
	ShaderParams localParams;

	getObjectId(objects, get_global_id(0), objectsCount, &objectId, &relativeId);
	localParams = params[objectId];
	switch (objects[objectId].vertexBuffer.topology)
	{
	case GR_PRIMITIVE_TOPOLOGY_POINT:
		primitiveController1(objects + objectId, &localParams, relativeId, shaderGlobal);
	case GR_PRIMITIVE_TOPOLOGY_LINE:
		primitiveController2(objects + objectId, &localParams, relativeId, shaderGlobal);
	case GR_PRIMITIVE_TOPOLOGY_TRIANGLE:
		primitiveController3(objects + objectId, &localParams, relativeId, shaderGlobal);
	default:
		break;
	}
}