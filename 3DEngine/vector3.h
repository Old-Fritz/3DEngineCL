#ifndef VECTOR3_H
#define VECTOR3_H

/// Describe three-component vector

typedef struct _m3dVector3 {
	float x;
	float y;
	float z;
} m3dVector3;

m3dVector3* m3dVec3Add(m3dVector3* outVec, const m3dVector3* vec1, const m3dVector3* vec2);
m3dVector3* m3dVec3Sub(m3dVector3* outVec, const m3dVector3* vec1, const m3dVector3* vec2);
m3dVector3* m3dVec3Cross(m3dVector3* outVec, const m3dVector3* vec1, const m3dVector3* vec2);
float m3dVec3Dot(const m3dVector3* vec1, const m3dVector3* vec2);
float m3dVec3Length(const m3dVector3* vec);
m3dVector3* m3dVec3Normalize(m3dVector3* outVec, const m3dVector3* vec);
m3dVector3* m3dVec3Scale(m3dVector3* outVec, const m3dVector3* vec, float scale);

#endif