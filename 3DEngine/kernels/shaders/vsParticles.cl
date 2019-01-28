
typedef struct VertexInputType
{
	m3dVector3 position;
	m3dVector3 speed;
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
	float change;
} ShaderParams;

int VertexShader(__global  VertexInputType* input, ShaderParams* params, PixelInputType* output)
{
	float G = 6;
	float distSquare, force;
	VertexInputType lInput = *input;

	// set forse
	distSquare = lInput.position.x*lInput.position.x
		+ lInput.position.y*lInput.position.y
		+ lInput.position.z*lInput.position.z;
	force = G / distSquare * params->change;

	lInput.speed.x += -lInput.position.x*force;
	lInput.speed.y += -lInput.position.y*force;
	lInput.speed.z += -lInput.position.z*force;
		
	// change particles position
	lInput.position.x += lInput.speed.x * params->change;
	lInput.position.y += lInput.speed.y * params->change;
	lInput.position.z += lInput.speed.z * params->change;

	*input = lInput;

	// calculate color
	output->color.x = lInput.position.x*64 + 128.0;
	if (output->color.x < 0)
		output->color.x = 0;
	if (output->color.x > 255)
		output->color.x = 255;

	output->color.y = lInput.position.y * 64 + 128.0;
	if (output->color.y < 0)
		output->color.y = 0;
	if (output->color.y > 255)
		output->color.y = 255;

	output->color.z = lInput.position.z * 64 + 128.0;
	if (output->color.z < 0)
		output->color.z = 0;
	if (output->color.z > 255)
		output->color.z = 255;

	// calculate projected position
	m3dVec3TransformCoord(&(output->position), &(lInput.position), &(params->worldMatrix));
	m3dVec3TransformCoord(&(output->position), &(output->position), &(params->viewMatrix));
	m3dVec3Projection(&(output->position), &(output->position), &(params->projectionMatrix));


	return 1;
}
