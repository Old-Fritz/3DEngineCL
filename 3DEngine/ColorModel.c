#include "ColorModel.h"
#include "LogManager.h"
#include "GraphicSystem.h"

int mdColorCreate(mdColorModel* model)
{
	int result;
	m3dMatrix projectionMatrix;
	mdColorModelVertex verticies[4] = { { {-0.3,0.3,1}, {255,0,0, 0} },{ { 0.3,0.3,1},{0,255,0, 0} },{ { 0.3,-0.3,1}, {0,0,255,0} },{ {-0.3,-0.3,1}, {0,0,0,255} } };
	int indicies[6] = { 0, 1, 2, 2,3,0 };

	result = mdBaseModelInit(&(model->model), verticies, indicies, 4, 6, sizeof(mdColorModelVertex), GR_PRIMITIVE_TOPOLOGY_TRIANGLE);
	if (!result)
	{
		logs("can't create color model");
		return 0;
	}

	return 1;
}
void mdColorShutdown(mdColorModel* model)
{
	mdShutdown(&(model->model));
}