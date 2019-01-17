#include "vector3.h"
#include "math.h"

m3dVector3* m3dVec3Add(m3dVector3* outVec, const m3dVector3* vec1, const m3dVector3* vec2)
{
	outVec->x = vec1->x + vec2->x;
	outVec->y = vec1->y + vec2->y;
	outVec->z = vec1->z + vec2->z;

	return outVec;
}

m3dVector3* m3dVec3Sub(m3dVector3* outVec, const m3dVector3* vec1, const m3dVector3* vec2)
{
	outVec->x = vec1->x - vec2->x;
	outVec->y = vec1->y - vec2->y;
	outVec->z = vec1->z - vec2->z;

	return outVec;
}

m3dVector3* m3dVec3Cross(m3dVector3* outVec, const m3dVector3* vec1, const m3dVector3* vec2)
{
	outVec->x = vec1->y*vec2->z - vec1->z*vec2->y;
	outVec->y = vec1->z*vec2->x - vec1->x*vec2->z;
	outVec->z = vec1->x*vec2->y - vec1->y*vec2->x;

	return outVec;
}

float m3dVec3Dot(const m3dVector3* vec1, const m3dVector3* vec2)
{
	return vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z;
}

float m3dVec3Length(const m3dVector3* vec)
{
	return sqrtf(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z);
}

m3dVector3* m3dVec3Normalize(m3dVector3* outVec, const  m3dVector3* vec)
{
	float length = m3dVec3Length(vec);
	float invLength = 1 / length;
	outVec->x = vec->x*invLength;
	outVec->y = vec->y*invLength;
	outVec->z = vec->z*invLength;

	return outVec;
}

m3dVector3* m3dVec3Scale(m3dVector3* outVec, const m3dVector3* vec, float scale)
{
	outVec->x = vec->x*scale;
	outVec->y = vec->y*scale;
	outVec->z = vec->z*scale;

	return outVec;
}

m3dVector3* m3dVec3Copy(m3dVector3* outVec, const m3dVector3* vec)
{
	outVec->x = vec->x;
	outVec->y = vec->y;
	outVec->z = vec->z;

	return outVec;
}