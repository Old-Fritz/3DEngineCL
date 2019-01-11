#include "Shader.h"

static struct ShaderElement
{
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;
	void* params;
};

struct _grShader
{
	cl_command_queue queue;
	cl_kernel kernel;
	struct ShaderElement* shaderElements;
};