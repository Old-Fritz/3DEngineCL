#ifndef SHADER_H
#define SHADER_H

#include "CL/cl.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

/// Object that control render operation with verticies in graphic card

typedef struct _grShader* grShader;
typedef struct grShaderGlobal
{
	void* outBuffer;
	void* depthBuffer;
	void* accessBuffer;
	int screenWidth, screenHegiht;
	float farZ, nearZ;
	float left, right, top, bottom;
} grShaderGlobal;

// Create shader and initialize it from files with functions for vertex and pixel shaders
int grCreateShader(grShader* shader, const  char* vsFilename, const  char* psFilename, size_t paramSize);
// Release shader
void grShutdownShader(grShader shader);
// Add model element before execution of shader (with all models in one time)
int grAddToShaderQueue(grShader shader, grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, void* params);
// Execute shader and clear shader queue
int grExecuteShader(grShader shader, void* outBuffer);
// Work with global shader params
int grGetShaderGlobal(grShader shader, grShaderGlobal*shaderGlobal);
int grSetShaderGlobal(grShader shader, grShaderGlobal* shaderGlobal);
int grSetDefaultShaderGlobal(grShader shader);
// Wait for end of execution
int grFinishShader(grShader shader);

#endif