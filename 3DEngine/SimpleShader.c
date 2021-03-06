#include "SimpleShader.h"
#include "vector3.h"
#include "LogManager.h"

static grShader shader;

int grCreateSimpleShader(char* vsShader, char* psShader)
{
	int result;

	result = grCreateShader(&shader, vsShader, psShader, sizeof(grSimpleShaderParams));
	if(!result)
	{
		logs("can't create simple shader");
		return 0;
	}

	return 1;
}
void grShutdownSimpleShader()
{
	grShutdownShader(shader);
}
int grRenderSimpleShader(grVertexBuffer vertexBuffer, grIndexBuffer indexBuffer, grSimpleShaderParams params)
{
	int result;

	result = grAddToShaderQueue(shader,vertexBuffer, indexBuffer, &params);
	if(!result)
	{
		logs("can't add element to simple shader");
		return 0;
	}

	return 1;
}
int grExecuteSimpleShader(void* outBuffer)
{
	int result;

	result = grExecuteShader(shader, outBuffer);
	if(!result)
	{
		logs("can't execute simple shader");
		return 0;
	}

	return 1;
}

int grFinishSimpleShader()
{
	int result;

	result = grFinishShader(shader);
	if(!result)
	{
		logs("can't finish simple shader");
		return 0;
	}

	return 1;
}
