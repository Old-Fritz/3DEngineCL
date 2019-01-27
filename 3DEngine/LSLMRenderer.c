#include "LSLMRenderer.h"
#include "LightShader.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int renderLSLM(mdLightModel* lightModel, mdDiffuseLight* light)
{
	int result;
	grLightShaderParams params;
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;
	m3dVector3 rotation;
	m3dVector3 position;
	m3dMatrix rotateMatrix;
	m3dMatrix translateMatrix;

	// fill params
	m3dMatrixIdentity(&(params.worldMatrix));
	m3dMatrixIdentity(&(params.viewMatrix));
	grGetProjectionMatrix(&(params.projectionMatrix));
	params.modelColor = lightModel->color;
	mdGetPosition(&(light->model), &(params.lightPos));
	params.lightColor = light->color;
	params.lightIntensity = light->intencity;

	// get params of model
	mdGetPosition(&(lightModel->model), &position);
	mdGetRotation(&(lightModel->model), &rotation);

	// change world matrix
	m3dMatrixRotationYawPitchRoll(&rotateMatrix, rotation.y, rotation.x, rotation.z);
	//m3dMatrixMultiply(&(params.worldMatrix), &(params.worldMatrix), &rotateMatrix);
	m3dMatrixTranslation(&translateMatrix, position.x, position.y, position.z);
	//m3dMatrixMultiply(&(params.worldMatrix), &(params.worldMatrix), &translateMatrix);

	// get buffers and render
	mdGetBuffers(&(lightModel->model), &vertexBuffer, &indexBuffer);

	result = grRenderLightShader(vertexBuffer, indexBuffer, params);
	if (!result)
	{
		logs("can't render light model in light shader");
		return 0;
	}

	return 1;
}
