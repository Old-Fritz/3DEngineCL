#include "SimpleModel.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int mdSimpleCreate(mdSimpleModel* model)
{
	int result;
	m3dMatrix projectionMatrix;
	mdSimpleModelVertex verticies[4] = { { -100,100,5 },{ -50,-50,3 },{ 100,-100,5 },{ -100,-100,5 } };
	//mdSimpleModelVertex verticies[4] = { { 50,0,50 },{ 100,0,100 },{ 150,0,150 },{ 200,0,200 } };
	int indicies[6] = { 0, 1, 2, 2,3,0 };

	grGetProjectionMatrix(&projectionMatrix);
	for (int i = 0;i<4;i++)
	{
		m3dVec3Projection(verticies + i, verticies + i, &projectionMatrix);
	}

	result = mdBaseModelInit(&(model->model), verticies, indicies, 4, 6, sizeof(mdSimpleModelVertex), GR_PRIMITIVE_TOPOLOGY_TRIANGLE);
	if (!result)
	{
		logs("can't create simple model");
		return 0;
	}

	return 1;
}
void mdSimpleShutdown(mdSimpleModel* model)
{
	mdShutdown(&(model->model));
}