#include "LightModel.h"
#include "LogManager.h"
#include "GraphicSystem.h"
#include "stdio.h"
#include "stdlib.h"

static int loadFromFile(const char* filename, mdLightModelVertex** verticies, int** indicies, int* indexCount, int* vertexCount)
{
	FILE* file;
	int result, i;
	//int vertexCount;

	result = fopen_s(&file, filename, "r");
	if(result)
	{
		logs("can't open model file");
		return 0;
	}

	fscanf_s(file, "%d\n", vertexCount);
	*indexCount = *vertexCount;

	*verticies = malloc(sizeof(mdLightModelVertex)*(*vertexCount));
	*indicies = malloc(sizeof(int)*(*vertexCount));

	for(i = 0; i<(*vertexCount);i++)
	{
		fscanf_s(file, "%f %f %f %f %f %f\n", &((*verticies)[i].position.x), &((*verticies)[i].position.y), &((*verticies)[i].position.z),
			&((*verticies)[i].normal.x), &((*verticies)[i].normal.y), &((*verticies)[i].normal.z));
		(*indicies)[i] = i;
	}
	return 1;
}

int mdLightCreate(mdLightModel* model, const char* filename)
{
	int result;
	m3dMatrix projectionMatrix;
	mdLightModelVertex* verticies;
	int* indicies;
	int indexCount, vertexCount;

	result = loadFromFile(filename, &verticies, &indicies,&indexCount, &vertexCount);
	if (!result)
		return 0;

	result = mdBaseModelInit(&(model->model), verticies, indicies, vertexCount, indexCount, sizeof(mdLightModelVertex), GR_PRIMITIVE_TOPOLOGY_TRIANGLE);
	if (!result)
	{
		logs("can't create light model");
		return 0;
	}

	free(indicies);
	free(verticies);

	return 1;
}
void mdLightShutdown(mdLightModel* model)
{
	mdShutdown(&(model->model));
}