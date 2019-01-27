#include "ColorShader.h"
#include "vector3.h"
#include "LogManager.h"

static grShader shader;

int grCreateColorShader(char* vsShader, char* psShader)
{
	int result;

	result = grCreateShader(&shader, vsShader, psShader, sizeof(grColorShaderParams));
	if (!result)
	{
		logs("can't create color shader");
		return 0;
	}

	return 1;
}
void grShutdownColorShader()
{
	grShutdownShader(shader);
}
int grRenderColorShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grColorShaderParams params)
{
	int result;

	result = grAddToShaderQueue(shader, vertexBuffer, indexBuffer, &params);
	if (!result)
	{
		logs("can't add element to color shader");
		return 0;
	}

	return 1;
}
int grExecuteColorShader(void* outBuffer)
{
	int result;

	result = grExecuteShader(shader, outBuffer);
	if (!result)
	{
		logs("can't execute color shader");
		return 0;
	}

	return 1;
}

int grFinishColorShader()
{
	int result;

	result = grFinishShader(shader);
	if (!result)
	{
		logs("can't finish color shader");
		return 0;
	}

	return 1;
}
