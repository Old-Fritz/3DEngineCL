#include "SSSMRenderer.h"
#include "SimpleShader.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int renderSSSM(mdSimpleModel* simpleModel)
{
	int result;
	grSimpleShaderParams params;
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;

	// fill params
	params.color = simpleModel->color;
	m3dMatrixIdentity(&(params.worldMatrix));
	m3dMatrixIdentity(&(params.viewMatrix));
	grGetProjectionMatrix(&(params.projectionMatrix));

	// get buffers and render
	mdGetBuffers(&(simpleModel->model), &vertexBuffer, &indexBuffer);

	result = grRenderSimpleShader(vertexBuffer, indexBuffer, params);
	if(!result)
	{
		logs("can't render simple model in simple shader");
		return 0;
	}

	return 1;
}
