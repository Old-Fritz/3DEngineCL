#include "ShaderManager.h"
#include "OpenCL.h"

// Initialize all shaders
int grCreateAllShaders()
{
	int result;
	
	result = grCreateSimpleShader("kernels/shaders/vsSimple.cl", "kernels/shaders/psSimple.cl");
	if (!result)
		return 0;

	result = grCreateColorShader("kernels/shaders/vsColor.cl", "kernels/shaders/psColor.cl");
	if (!result)
		return 0;

	result = grCreateLightShader("kernels/shaders/vsLight.cl", "kernels/shaders/psLight.cl");
	if (!result)
		return 0;

	result = grCreateParticlesShader("kernels/shaders/vsParticles.cl", "kernels/shaders/psParticles.cl");
	if (!result)
		return 0;

	return 1;
}

// Release all resources connected with shaders
void grShutdownAllShaders()
{
	grShutdownParticlesShader();
	grShutdownLightShader();
	grShutdownColorShader();
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

	result = grExecuteColorShader(outBuffer);
	if (!result)
		return 0;

	result = grExecuteLightShader(outBuffer);
	if (!result)
		return 0;

	result = grExecuteParticlesShader(outBuffer);
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

	result = grFinishColorShader();
	if (!result)
		return 0;

	result = grFinishLightShader();
	if (!result)
		return 0;

	result = grFinishParticlesShader();
	if (!result)
		return 0;

	return 1;
}
