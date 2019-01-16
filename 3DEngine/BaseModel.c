#include "BaseModel.h"

struct _mdBaseModel {
	grVertexBuffer vertexBuffer;
	grIndexBuffer indexBuffer;
	int vertexCount;
	int indexCount;

	m3dVector3 position;
	m3dVector3 rotation;
};