#include "VectorTransform.h"


m3dVector2* m3dVec2TransformCoord(m3dVector2* outVec, const m3dVector2* vec, const m3dMatrix* matrix)
{
	m3dVector4 transVec = { vec->x, vec->y, 0, 1 };

	m3dVec4TransformCoord(&transVec, &transVec, matrix);
	m3dVec4Scale(&transVec, &transVec, 1 / transVec.w);
	m3dVec2Copy(outVec, &transVec);

	return outVec;
}

m3dVector3* m3dVec3TransformCoord(m3dVector3* outVec, const m3dVector3* vec, const m3dMatrix* matrix)
{
	m3dVector4 transVec = {vec->x, vec->y, vec->z, 1};

	m3dVec4TransformCoord(&transVec, &transVec, matrix);
	m3dVec4Scale(&transVec, &transVec, 1 / transVec.w);
	m3dVec3Copy(outVec, &transVec);

	return outVec;
}

m3dVector4* m3dVec4TransformCoord(m3dVector4* outVec, const m3dVector4* vec, const m3dMatrix* matrix)
{
	m3dVector4 tempVec;

	tempVec.x = vec->x*matrix->_11 + vec->y*matrix->_21 + vec->z*matrix->_31 + vec->w*matrix->_41;
	tempVec.y = vec->x*matrix->_12 + vec->y*matrix->_22 + vec->z*matrix->_32 + vec->w*matrix->_42;
	tempVec.z = vec->x*matrix->_13 + vec->y*matrix->_23 + vec->z*matrix->_33 + vec->w*matrix->_43;
	tempVec.w = vec->x*matrix->_14 + vec->y*matrix->_24 + vec->z*matrix->_34 + vec->w*matrix->_44;

	m3dVec4Copy(outVec, &tempVec);

	return outVec;
}

m3dVector3* m3dVec3Projection(m3dVector3* outVec, const m3dVector4* vec, const m3dMatrix* matrix)
{
	m3dVector4 transVec = { vec->x, vec->y, vec->z, 1 };

	m3dVec4TransformCoord(&transVec, &transVec, matrix);
	transVec.x /= transVec.w;
	transVec.y /= transVec.w;

	m3dVec3Copy(outVec, &transVec);

	return outVec;
}
