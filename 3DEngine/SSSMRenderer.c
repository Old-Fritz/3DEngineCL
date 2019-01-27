#include "SSSMRenderer.h"
#include "SimpleShader.h"
#include "LogManager.h"
#include "GraphicSystem.h"
#include <d3dx9math.h>

int renderSSSM(mdSimpleModel* simpleModel)
{
	int result;
	grSimpleShaderParams params;
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;
	m3dMatrix rotateMatrix;
	m3dMatrix translateMatrix;
	m3dVector3 vec = {0.4,0.4,1};

	// fill params
	params.color = simpleModel->color;
	m3dMatrixIdentity(&(params.worldMatrix));
	m3dMatrixIdentity(&(params.viewMatrix));
	grGetProjectionMatrix(&(params.projectionMatrix));

	// change world matrix
	D3DXMatrixRotationX(&rotateMatrix,-0.3);
	m3dMatrixMultiply(&(params.worldMatrix), &(params.worldMatrix), &rotateMatrix);
	//m3dMatrixTranslation(&translateMatrix, 0, 0, 1);
	//m3dMatrixMultiply(&(params.worldMatrix), &(params.worldMatrix), &translateMatrix);

	m3dVec3TransformCoord(&(vec), &(vec), &(params.worldMatrix));
	m3dVec3TransformCoord(&(vec), &(vec), &(params.viewMatrix));
	m3dVec3Projection(&(vec), &(vec), &(params.projectionMatrix));

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
