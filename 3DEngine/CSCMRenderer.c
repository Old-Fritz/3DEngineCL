#include "CSCMRenderer.h"
#include "ColorShader.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int renderCSCM(mdColorModel* simpleModel)
{
	int result;
	grColorShaderParams params;
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;

	// fill params
	m3dMatrixIdentity(&(params.worldMatrix));
	m3dMatrixIdentity(&(params.viewMatrix));
	grGetProjectionMatrix(&(params.projectionMatrix));

	// get buffers and render
	mdGetBuffers(&(simpleModel->model), &vertexBuffer, &indexBuffer);

	result = grRenderColorShader(vertexBuffer, indexBuffer, params);
	if (!result)
	{
		logs("can't render color model in color shader");
		return 0;
	}

	return 1;
}
