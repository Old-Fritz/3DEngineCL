#include "../libs/math3d.cl"

typedef struct VertexInputType
{
	m3dVector3 position;
	m3dVector4 color;
	m3dMatrix worldMatrix;
	m3dMatrix projectionMatrix;
	m3dMatrix viewMatrix;
} VertexInputType;

typedef struct PixelInputType
{
	m3dVector3 position;
	m3dVector4 color;
} PixelInputType;

PixelInputType VertexShader(VertexInputType input)
{
	PixelInputType output;

	// set const color parameter
	output.color = input.color;

	// calculate projected position
	m3dVec3TransformCoord(&(output.position), &(input.position), &(input.worldMatrix));
	m3dVec3TransformCoord(&(output.position), &(output.position), &(input.viewMatrix));
	m3dVec3TransformCoord(&(output.position), &(output.position), &(input.projectionMatrix));

	return output;
}