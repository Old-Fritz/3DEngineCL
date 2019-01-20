#include "SimpleModel.h"
#include "LogManager.h"

int mdSimpleCreate(mdSimpleModel* model)
{
	int result;
	mdSimpleModelVertex verticies[4] = { { -10,10,5 },{ 10,10,5 },{ 10,-10,5 },{ -10,-10,5 } };
	int indicies[6] = { 0, 1, 2, 2,3,1 };

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