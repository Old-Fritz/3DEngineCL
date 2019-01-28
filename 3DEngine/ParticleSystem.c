#include "ParticlesSystem.h"
#include "LogManager.h"
#include "LightModel.h"
#include <stdlib.h>

static float randFloat()
{
	return (float)(rand()*2 - RAND_MAX)/RAND_MAX*2;
}

static int generateParticles(mdParticleVertex** verticies, int** indicies, int count)
{
	int result, i;

	*verticies = malloc(sizeof(mdParticleVertex)*count);
	if (!*verticies)
		return 0;
	*indicies = malloc(sizeof(int)*count);
	if (!*indicies)
		return 0;

	for(i = 0;i<count;i++)
	{
		(*verticies)[i].position.x = randFloat();
		(*verticies)[i].position.y = randFloat();
		(*verticies)[i].position.z = randFloat();
		(*verticies)[i].speed.x = randFloat();
		(*verticies)[i].speed.y = randFloat();
		(*verticies)[i].speed.z = randFloat();

		(*indicies)[i] = i;
	}

	return 1;
}

int mdParticlesSystemCreate(mdParticlesSystem* model, int count)
{
	int result;
	m3dMatrix projectionMatrix;
	mdLightModelVertex* verticies;
	int* indicies;

	result = generateParticles(&verticies, &indicies, count);
	if (!result)
		return 0;

	result = mdBaseModelInit(&(model->model), verticies, indicies, count, count, sizeof(mdParticleVertex), GR_PRIMITIVE_TOPOLOGY_POINT);
	if (!result)
	{
		logs("can't create particle system model");
		return 0;
	}

	return 1;
}
void mdParticlesSystemShutdown(mdParticlesSystem* model)
{
	mdShutdown(&(model->model));
}