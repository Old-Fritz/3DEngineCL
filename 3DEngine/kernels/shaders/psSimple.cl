#include "../libs/math3d.cl"
#include "../libs/shaderBase.cl"

typedef struct PixelInputType
{
	m3dVector3 position;
	m3dVector4 color;
} PixelInputType;

m3dVector4 PixelInput(PixelInputType input)
{
	return input.color;
}