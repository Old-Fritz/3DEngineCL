#include "ParticlesShader.h"
#include "LogManager.h"

static grShader shader;

int grCreateParticlesShader(char* vsShader, char* psShader)
{
	int result;

	result = grCreateShader(&shader, vsShader, psShader, sizeof(grParticlesShaderParams));
	if (!result)
	{
		logs("can't create particles shader");
		return 0;
	}

	return 1;
}
void grShutdownParticlesShader()
{
	grShutdownShader(shader);
}
int grRenderParticlesShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grParticlesShaderParams params)
{
	int result;

	result = grAddToShaderQueue(shader, vertexBuffer, indexBuffer, &params);
	if (!result)
	{
		logs("can't add element to particles shader");
		return 0;
	}

	return 1;
}
int grExecuteParticlesShader(void* outBuffer)
{
	int result;

	result = grExecuteShader(shader, outBuffer);
	if (!result)
	{
		logs("can't execute particles shader");
		return 0;
	}

	return 1;
}

int grFinishParticlesShader()
{
	int result;

	result = grFinishShader(shader);
	if (!result)
	{
		logs("can't finish particles shader");
		return 0;
	}

	return 1;
}
