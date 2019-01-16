#ifndef VECTOR4_H
#define VECTOR4_H

/// Describe four-component vector

typedef struct _m3dVector4 {
	float x;
	float y;
	float z;
	float w;
} m3dVector4;

m3dVector4* m3dVec4Add(m3dVector4* outVec, const m3dVector4* vec1, const m3dVector4* vec2);
m3dVector4* m3dVec4Sub(m3dVector4* outVec, const m3dVector4* vec1, const m3dVector4* vec2);
float m3dVec4Dot(const m3dVector4* vec1, const m3dVector4* vec2);
float m3dVec4Length(const m3dVector4* vec);
m3dVector4* m3dVec4Normalize(m3dVector4* outVec, const m3dVector4* vec);
m3dVector4* m3dVec4Scale(m3dVector4* outVec, const m3dVector4* vec, float scale);

#endif