
typedef struct VertexInputType
{
	m3dVector3 position;
	m3dVector4 color;
} VertexInputType;

typedef struct PixelInputType
{
	m3dVector3 position;
	m3dVector4 color;
} PixelInputType;

typedef struct ShaderParams
{
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
} ShaderParams;

int VertexShader(__global VertexInputType* input, ShaderParams* params, PixelInputType* output)
{
	VertexInputType lInput = *input;

	// calculate projected position
	m3dVec3TransformCoord(&(output->position), &(lInput.position), &(params->worldMatrix));
	m3dVec3TransformCoord(&(output->position), &(output->position), &(params->viewMatrix));
	m3dVec3Projection(&(output->position), &(output->position), &(params->projectionMatrix));
	output->color = lInput.color;

	return 1;
}
