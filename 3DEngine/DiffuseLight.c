#include "DiffuseLight.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int mdDiffuseLightCreate(mdDiffuseLight* model)
{
	int result;
	m3dMatrix projectionMatrix;
	mdDiffuseLightVertex verticies[1] = { {0,0,0} };
	int indicies[1] = { 0 };

	result = mdBaseModelInit(&(model->model), verticies, indicies, 1, 1, sizeof(mdDiffuseLightVertex), GR_PRIMITIVE_TOPOLOGY_POINT);
	if (!result)
	{
		logs("can't create diffuse light");
		return 0;
	}

	return 1;
}
void mdDiffuseLightShutdown(mdDiffuseLight* model)
{
	mdShutdown(&(model->model));
}