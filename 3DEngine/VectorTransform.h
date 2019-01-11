#ifndef VECTOR_TRANSFORM_H
#define VECTOR_TRANSFORM_H
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "Matrix.h"

/// determine transform operations with vectors and matrix

// vector2 transform
m3dVector2* m3dVec2TransformCoord(m3dVector2* vecOut, const m3dVector2* vec, const m3dMatrix* matrix);

// vector3 transform
m3dVector3* m3dVec3TransformCoord(m3dVector3* vecOut, const m3dVector3* vec, const m3dMatrix* matrix);

// vector4 transform
m3dVector4* m3dVec4TransformCoord(m3dVector4* vecOut, const m3dVector4* vec, const m3dMatrix* matrix);


#endif