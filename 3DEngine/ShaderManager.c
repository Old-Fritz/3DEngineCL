#include "ShaderManager.h"
#include "OpenCL.h"

// Initialize all shaders
int grCreateAllShaders()
{
	int result;
	
	result = grCreateSimpleShader("kernels/shaders/vsSimple.cl", "kernels/shaders/psSimple.cl");
	if (!result)
		return 0;

	return 1;
}

// Release all resources connected with shaders
void grShutdownAllShaders()
{
	grShutdownSimpleShader();
}

// Execute all shaders
int grExecuteAllShaders()
{
	int result;
	void* outBuffer = clGetOutBufferPtr();

	result = grExecuteSimpleShader(outBuffer);
	if (!result)
		return 0;

	return 1;
}

int grFinishAllShaders()
{
	int result;

	result = grFinishSimpleShader();
	if (!result)
		return 0;

	return 1;
}
