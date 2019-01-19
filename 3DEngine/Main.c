#include "System.h"
#include "Math3d.h"
#include "stdio.h"
#include <stdlib.h>
#include "Camera.h"
#include <d3dx9math.h>

void testMatrix();

int main()
{
	int result;

	testMatrix();
	return;

	result = sysInit();
	if(!result)
		return 0;

	sysRun();
	sysShutdown();


	return 0;
}

void testMatrix()
{
	//grInitGraphicSystem();
	grCameraInit();

	m3dMatrix projectionMatrix, worldMatrix, viewMatrix;
	m3dVector4 position = {30, 4120,1000, 1};

	//m3dMatrixPerspectiveFov(&projectionMatrix, 45.0 / 180 * 3.1415, 1920.0 / 1080, 0.1, 1000);
	//m3dMatrixIdentity(&worldMatrix);
	//grGetViewMatrix(&viewMatrix);

	//m3dMatrixPerspectiveFov(&projectionMatrix, 45.0/180*3.1415, 1920.0/1080,0.1, 1000);

	//m3dVec4TransformCoord(&position, &position, &worldMatrix);
	//m3dVec4TransformCoord(&position, &position, &viewMatrix);
	//m3dVec4TransformCoord(&position, &position, &projectionMatrix);

	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 45.0 / 180 * 3.1415, 1920.0 / 1080, 0.1, 100000);
	D3DXVec4Transform(&position, &position, &projectionMatrix);

	printf("%f %f %f %f\n", position.x, position.y, position.z, position.w);

	system("pause");
}