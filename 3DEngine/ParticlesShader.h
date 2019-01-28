#ifndef PARTICLES_SHADER_H
#define PARTICLES_SHADER_H

#include "Shader.h"
#include "VectorTransform.h"

/// Simple shader that draw verticies with providied color

typedef struct grParticlesShaderParams
{
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
	float change;
} grParticlesShaderParams;

int grCreateParticlesShader(char* vsShader, char* psShader);
void grShutdownParticlesShader();
int grRenderParticlesShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grParticlesShaderParams params);
int grExecuteParticlesShader(void* outBuffer);
int grFinishParticlesShader();

#endif