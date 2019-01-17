#ifndef VECTOR2_H
#define VECTOR2_H

/// Describe two-component vector

typedef struct _m3dVector2{
	float x;
	float y;
} m3dVector2;

m3dVector2* m3dVec2Add(m3dVector2* outVec, const m3dVector2* vec1, const m3dVector2* vec2);
m3dVector2* m3dVec2Sub(m3dVector2* outVec, const m3dVector2* vec1, const m3dVector2* vec2);
float m3dVec2Dot(const m3dVector2* vec1, const m3dVector2* vec2);
float m3dVec2Length(const m3dVector2* vec);
m3dVector2* m3dVec2Normalize(m3dVector2* outVec, const  m3dVector2* vec);
m3dVector2* m3dVec2Scale(m3dVector2* outVec, const m3dVector2* vec, float scale);
m3dVector2* m3dVec2Copy(m3dVector2* outVec, const m3dVector2* vec);

#endif