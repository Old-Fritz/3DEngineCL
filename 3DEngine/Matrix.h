#ifndef MATRIX_H
#define MATRIX_H
#include "vector3.h"

/// Describe 4x4 matrix

typedef struct _m3dMatrix {
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
} m3dMatrix;

// operation with matricies
float m3dMatrixDeterminant(const m3dMatrix* matrix);
m3dMatrix* m3dMatrixInverse(m3dMatrix* outMatrix, const m3dMatrix* matrix);
m3dMatrix* m3dMatrixMultiply(m3dMatrix* outMatrix, const m3dMatrix* matrix1, const m3dMatrix* matrix2);
m3dMatrix* m3dMatrixTranspose(m3dMatrix* outMatrix, const m3dMatrix* matrix);

// building matricies (left-handed)
m3dMatrix* m3dMatrixIdentity(m3dMatrix* outMatrix);
m3dMatrix* m3dMatrixRotationAxis(m3dMatrix* outMatrix, const m3dVector3* axis, float angle);
m3dMatrix* m3dMatrixRotationYawPitchRoll(m3dMatrix* outMatrix, float yaw, float pitch, float roll);
m3dMatrix* m3dMatrixScaling(m3dMatrix* outMatrix, float x, float y, float z);
m3dMatrix* m3dMatrixTranslation(m3dMatrix* outMatrix, float x, float y, float z);
m3dMatrix* m3dMatrixOrtho(m3dMatrix* outMatrix, float width, float height, float minZ, float maxZ);
m3dMatrix* m3dMatrixPerspective(m3dMatrix* outMatrix, float width, float height, float minZ, float maxZ);
m3dMatrix* m3dMatrixPerspectiveFow(m3dMatrix* outMatrix, float fov, float aspect, float minZ, float maxZ);
m3dMatrix* m3dMatrixLookAt(m3dMatrix* outMatrix, const m3dVector3* eye, const m3dVector3* at, const m3dVector3* up);

#endif