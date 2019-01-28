
typedef struct VertexInputType
{
	m3dVector3 position;
	m3dVector3 normal;
} VertexInputType;

typedef struct PixelInputType
{
	m3dVector3 position;
	m3dVector3 normal;
	m3dVector3 lightPos;
} PixelInputType;

typedef struct ShaderParams
{
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
	m3dVector4 modelColor;
	m3dVector3 lightPos;
	m3dVector4 lightColor;
	float lightIntensity;
} ShaderParams;

int VertexShader(__global VertexInputType* input, ShaderParams* params, PixelInputType* output)
{
	VertexInputType lInput = *input;
	m3dVector3 worldPosition;


	// calculate projected position
	m3dVec3TransformCoord(&(output->position), &(lInput.position), &(params->worldMatrix));
	m3dVec3TransformCoord(&(output->position), &(output->position), &(params->viewMatrix));
	m3dVec3Projection(&(output->position), &(output->position), &(params->projectionMatrix));

	// calculate normal
	m3dVec3TransformCoord(&(output->normal), &(lInput.normal), &(params->worldMatrix));
	m3dVec3Normalize(&(output->normal), &(output->normal));

	// calculate light position
	m3dVec3TransformCoord(&(worldPosition), &(lInput.position), &(params->worldMatrix));
	m3dVec3Sub(&(output->lightPos), &(params->lightPos), &worldPosition);
	m3dVec3Normalize(&(output->lightPos), &(output->lightPos));

	return 1;
}
