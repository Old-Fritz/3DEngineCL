#include "LightShader.h"
#include "LogManager.h"

static grShader shader;

int grCreateLightShader(char* vsShader, char* psShader)
{
	int result;

	result = grCreateShader(&shader, vsShader, psShader, sizeof(grLightShaderParams));
	if (!result)
	{
		logs("can't create Light shader");
		return 0;
	}

	return 1;
}
void grShutdownLightShader()
{
	grShutdownShader(shader);
}
int grRenderLightShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grLightShaderParams params)
{
	int result;

	result = grAddToShaderQueue(shader, vertexBuffer, indexBuffer, &params);
	if (!result)
	{
		logs("can't add element to Light shader");
		return 0;
	}

	return 1;
}
int grExecuteLightShader(void* outBuffer)
{
	int result;

	result = grExecuteShader(shader, outBuffer);
	if (!result)
	{
		logs("can't execute Light shader");
		return 0;
	}

	return 1;
}

int grFinishLightShader()
{
	int result;

	result = grFinishShader(shader);
	if (!result)
	{
		logs("can't finish Light shader");
		return 0;
	}

	return 1;
}
