#include "PSPSRenderer.h"
#include "LogManager.h"
#include "GraphicSystem.h"
#include "Camera.h"
#include "ParticlesShader.h"

int renderPSPS(mdParticlesSystem* lightModel, float change)
{
	int result;
	grParticlesShaderParams params;
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;
	m3dVector3 rotation;
	m3dVector3 position;
	m3dMatrix rotateMatrix;
	m3dMatrix translateMatrix;

	// fill params
	params.change = change;
	grGetWorldMatrix(&(params.worldMatrix));
	grGetViewMatrix(&(params.viewMatrix));
	grGetProjectionMatrix(&(params.projectionMatrix));

	// get params of model
	mdGetPosition(&(lightModel->model), &position);
	mdGetRotation(&(lightModel->model), &rotation);

	// change world matrix
	m3dMatrixRotationYawPitchRoll(&rotateMatrix, rotation.y, rotation.x, rotation.z);
	m3dMatrixMultiply(&(params.worldMatrix), &(params.worldMatrix), &rotateMatrix);
	m3dMatrixTranslation(&translateMatrix, position.x, position.y, position.z);
	m3dMatrixMultiply(&(params.worldMatrix), &(params.worldMatrix), &translateMatrix);

	// get buffers and render
	mdGetBuffers(&(lightModel->model), &vertexBuffer, &indexBuffer);

	result = grRenderParticlesShader(vertexBuffer, indexBuffer, params);
	if (!result)
	{
		logs("can't render particles system in particles shader");
		return 0;
	}

	return 1;
}
