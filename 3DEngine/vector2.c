#include "vector2.h"
#include "math.h"

m3dVector2* m3dVec2Add(m3dVector2* outVec, const m3dVector2* vec1, const m3dVector2* vec2)
{
	outVec->x = vec1->x + vec2->x;
	outVec->y = vec1->y + vec2->y;

	return outVec;
}

m3dVector2* m3dVec2Sub(m3dVector2* outVec, const m3dVector2* vec1, const m3dVector2* vec2)
{
	outVec->x = vec1->x - vec2->x;
	outVec->y = vec1->y - vec2->y;

	return outVec;
}

float m3dVec2Dot(const m3dVector2* vec1, const m3dVector2* vec2)
{
	return vec1->x*vec2->x + vec1->y*vec2->y;
}

float m3dVec2Length(const m3dVector2* vec)
{
	return sqrtf(vec->x*vec->x + vec->y*vec->y);
}

m3dVector2* m3dVec2Normalize(m3dVector2* outVec, const  m3dVector2* vec)
{
	float length = m3dVec2Length(vec);
	float invLength = 1 / length;
	outVec->x = vec->x*invLength;
	outVec->y = vec->y*invLength;

	return outVec;
}

m3dVector2* m3dVec2Scale(m3dVector2* outVec, const m3dVector2* vec, float scale)
{
	outVec->x = vec->x*scale;
	outVec->y = vec->y*scale;

	return outVec;
}