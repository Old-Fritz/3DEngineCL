#include "System.h"
#include "vector3.h"
#include "Matrix.h"
#include "GraphicSystem.h"
#include "Camera.h"
#include <stdio.h>
#include <stdlib.h>

void testMatrix();

int main()
{
	int result;

	result = sysInit();
	if(!result)
		return 0;

	//testMatrix();

	//return;

	sysRun();
	sysShutdown();


	return 0;
}


void testMatrix()
{
	m3dMatrix projectionMatrix, worldMatrix, viewMatrix;
	m3dVector3 vectors[4] =  {{ -10,10,5 },{ 10,10,5 },{ 10,-10,5 },{ -10,-10,5 } };

	grGetProjectionMatrix(&projectionMatrix);
	grGetWorldMatrix(&worldMatrix);
	grGetViewMatrix(&viewMatrix);

	for(int i = 0;i<4;i++)
	{
		m3dVec3Projection(vectors + i, vectors + i, &(projectionMatrix));

		printf("%f %f %f\n", vectors[i].x, vectors[i].y, vectors[i].z);
	}

	system("pause");
}