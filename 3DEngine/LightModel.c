#include "LightModel.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int mdLightCreate(mdLightModel* model)
{
	int result;
	m3dMatrix projectionMatrix;
	mdLightModelVertex verticies[4] = { { { -0.3,0.3,1 },{ 0,0,-1 } },{ { 0.3,0.3,1 },{ 0,0,-1 } },{ { 0.3,-0.3,1 },{ 0,0,-1 } },{ { -0.3,-0.3,1 },{ 0,0,-1 } } };
	int indicies[6] = { 0, 1, 2, 2,3,0 };

	result = mdBaseModelInit(&(model->model), verticies, indicies, 4, 6, sizeof(mdLightModelVertex), GR_PRIMITIVE_TOPOLOGY_TRIANGLE);
	if (!result)
	{
		logs("can't create color model");
		return 0;
	}

	return 1;
}
void mdLightShutdown(mdLightModel* model)
{
	mdShutdown(&(model->model));
}