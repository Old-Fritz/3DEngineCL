#ifndef SHADER_H
#define SHADER_H

#include "CL/cl.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

/// Object that control render operation with verticies in graphic card

typedef struct _grShader* grShader;

// Create shader and initialize it from files with functions for vertex and pixel shaders
int grCreateShader(grShader* shader, char* vsFilename, char* psFilename);
// Release shader
void grShutdownShader(grShader shader);
// Add model element before execution of shader (with all models in one time)
int grAddToShaderQueue(grShader shader, grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, void* params);
// Execute shader and clear shader queue
int grExecuteShader(grShader shader);

#endif