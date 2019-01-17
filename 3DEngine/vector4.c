#include "vector4.h"
#include "math.h"

m3dVector4* m3dVec4Add(m3dVector4* outVec, const m3dVector4* vec1, const m3dVector4* vec2)
{
	outVec->x = vec1->x + vec2->x;
	outVec->y = vec1->y + vec2->y;
	outVec->z = vec1->z + vec2->z;
	outVec->w = vec1->w + vec2->w;

	return outVec;
}

m3dVector4* m3dVec4Sub(m3dVector4* outVec, const m3dVector4* vec1, const m3dVector4* vec2)
{
	outVec->x = vec1->x - vec2->x;
	outVec->y = vec1->y - vec2->y;
	outVec->z = vec1->z - vec2->z;
	outVec->w = vec1->w - vec2->w;

	return outVec;
}

float m3dVec4Dot(const m3dVector4* vec1, const m3dVector4* vec2)
{
	return vec1->x*vec2->x + vec1->y*vec2->y + vec1->z*vec2->z + vec1->w*vec2->w;
}

float m3dVec4Length(const m3dVector4* vec)
{
	return sqrtf(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z + vec->w*vec->w);
}

m3dVector4* m3dVec4Normalize(m3dVector4* outVec, const  m3dVector4* vec)
{
	float length = m3dVec4Length(vec);
	float invLength = 1 / length;
	outVec->x = vec->x*invLength;
	outVec->y = vec->y*invLength;
	outVec->z = vec->z*invLength;
	outVec->w = vec->w*invLength;

	return outVec;
}

m3dVector4* m3dVec4Scale(m3dVector4* outVec, const m3dVector4* vec, float scale)
{
	outVec->x = vec->x*scale;
	outVec->y = vec->y*scale;
	outVec->z = vec->z*scale;
	outVec->w = vec->w*scale;

	return outVec;
}

m3dVector4* m3dVec4Copy(m3dVector4* outVec, const m3dVector4* vec)
{
	outVec->x = vec->x;
	outVec->y = vec->y;
	outVec->z = vec->z;
	outVec->w = vec->w;

	return outVec;
}