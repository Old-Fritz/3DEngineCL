
typedef struct _m3dVector2 {
	float x;
	float y;
} m3dVector2;

typedef struct _m3dVector3 {
	float x;
	float y;
	float z;
} m3dVector3;

typedef struct _m3dVector4 {
	float x;
	float y;
	float z;
	float w;
} m3dVector4;

typedef struct _m3dMatrix {
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
} m3dMatrix;

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
	return sqrt(vec->x*vec->x + vec->y*vec->y);
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

m3dVector2* m3dVec2Copy(m3dVector2* outVec, const m3dVector2* vec)
{
	outVec->x = vec->x;
	outVec->y = vec->y;

	return outVec;
}

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
	return sqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z);
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
	return sqrt(vec->x*vec->x + vec->y*vec->y + vec->z*vec->z + vec->w*vec->w);
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

float determinant3(float _11, float _12, float _13,
	float _21, float  _22, float _23,
	float _31, float _32, float _33)
{
	return _11*_22*_33 -
		_11*_23*_32 -
		_12*_21*_33 +
		_12*_23*_31 +
		_13*_21*_32 -
		_13*_22*_31;
}

m3dMatrix* m3dMatrixCopy(m3dMatrix* outMatrix, const m3dMatrix* matrix)
{
	outMatrix->_11 = matrix->_11;
	outMatrix->_12 = matrix->_12;
	outMatrix->_13 = matrix->_13;
	outMatrix->_14 = matrix->_14;
	outMatrix->_21 = matrix->_21;
	outMatrix->_22 = matrix->_22;
	outMatrix->_23 = matrix->_23;
	outMatrix->_24 = matrix->_24;
	outMatrix->_31 = matrix->_31;
	outMatrix->_32 = matrix->_32;
	outMatrix->_33 = matrix->_33;
	outMatrix->_34 = matrix->_34;
	outMatrix->_41 = matrix->_41;
	outMatrix->_42 = matrix->_42;
	outMatrix->_43 = matrix->_43;
	outMatrix->_44 = matrix->_44;

	return outMatrix;
}

float m3dMatrixDeterminant(const m3dMatrix* matrix)
{
	float det1, det2, det3, det4;

	det1 = determinant3(matrix->_22, matrix->_23, matrix->_24,
		matrix->_32, matrix->_33, matrix->_34,
		matrix->_42, matrix->_43, matrix->_44);
	det2 = determinant3(matrix->_21, matrix->_23, matrix->_24,
		matrix->_31, matrix->_33, matrix->_34,
		matrix->_41, matrix->_43, matrix->_44);
	det3 = determinant3(matrix->_21, matrix->_22, matrix->_24,
		matrix->_31, matrix->_32, matrix->_34,
		matrix->_41, matrix->_42, matrix->_44);
	det4 = determinant3(matrix->_21, matrix->_22, matrix->_23,
		matrix->_31, matrix->_32, matrix->_33,
		matrix->_41, matrix->_42, matrix->_43);

	return matrix->_11*det1 - matrix->_12*det2 + matrix->_13*det3 - matrix->_14*det4;
}

m3dMatrix* m3dMatrixScale(m3dMatrix* outMatrix, const m3dMatrix* matrix, float scale)
{
	outMatrix->_11 = matrix->_11 * scale;
	outMatrix->_12 = matrix->_12 * scale;
	outMatrix->_13 = matrix->_13 * scale;
	outMatrix->_14 = matrix->_14 * scale;
	outMatrix->_21 = matrix->_21 * scale;
	outMatrix->_22 = matrix->_22 * scale;
	outMatrix->_23 = matrix->_23 * scale;
	outMatrix->_24 = matrix->_24 * scale;
	outMatrix->_31 = matrix->_31 * scale;
	outMatrix->_32 = matrix->_32 * scale;
	outMatrix->_33 = matrix->_33 * scale;
	outMatrix->_34 = matrix->_34 * scale;
	outMatrix->_41 = matrix->_41 * scale;
	outMatrix->_42 = matrix->_42 * scale;
	outMatrix->_43 = matrix->_43 * scale;
	outMatrix->_44 = matrix->_44 * scale;

	return outMatrix;
}

m3dMatrix* m3dMatrixInverse(m3dMatrix* outMatrix, const m3dMatrix* matrix)
{
	m3dMatrix tempMatrix;
	float det = m3dMatrixDeterminant(matrix);
	if (!det)
	{
		m3dMatrixCopy(outMatrix, matrix);
		return outMatrix;
	}

	tempMatrix._11 = determinant3(matrix->_22, matrix->_23, matrix->_24, matrix->_32, matrix->_33, matrix->_34, matrix->_42, matrix->_43, matrix->_44);
	tempMatrix._21 = -determinant3(matrix->_21, matrix->_23, matrix->_24, matrix->_31, matrix->_33, matrix->_34, matrix->_41, matrix->_43, matrix->_44);
	tempMatrix._31 = determinant3(matrix->_21, matrix->_22, matrix->_24, matrix->_31, matrix->_32, matrix->_34, matrix->_41, matrix->_42, matrix->_44);
	tempMatrix._41 = -determinant3(matrix->_21, matrix->_22, matrix->_23, matrix->_31, matrix->_32, matrix->_33, matrix->_41, matrix->_42, matrix->_43);
	tempMatrix._12 = -determinant3(matrix->_12, matrix->_13, matrix->_14, matrix->_32, matrix->_33, matrix->_34, matrix->_42, matrix->_43, matrix->_44);
	tempMatrix._22 = determinant3(matrix->_11, matrix->_13, matrix->_14, matrix->_31, matrix->_33, matrix->_34, matrix->_41, matrix->_43, matrix->_44);
	tempMatrix._32 = -determinant3(matrix->_11, matrix->_12, matrix->_14, matrix->_31, matrix->_32, matrix->_34, matrix->_41, matrix->_42, matrix->_44);
	tempMatrix._42 = determinant3(matrix->_11, matrix->_12, matrix->_13, matrix->_31, matrix->_32, matrix->_33, matrix->_41, matrix->_42, matrix->_43);
	tempMatrix._13 = determinant3(matrix->_12, matrix->_13, matrix->_14, matrix->_22, matrix->_23, matrix->_24, matrix->_42, matrix->_43, matrix->_44);
	tempMatrix._23 = -determinant3(matrix->_11, matrix->_13, matrix->_14, matrix->_21, matrix->_23, matrix->_24, matrix->_41, matrix->_43, matrix->_44);
	tempMatrix._33 = determinant3(matrix->_11, matrix->_12, matrix->_14, matrix->_21, matrix->_22, matrix->_24, matrix->_41, matrix->_42, matrix->_44);
	tempMatrix._43 = -determinant3(matrix->_11, matrix->_12, matrix->_13, matrix->_21, matrix->_22, matrix->_23, matrix->_41, matrix->_42, matrix->_43);
	tempMatrix._14 = -determinant3(matrix->_12, matrix->_13, matrix->_14, matrix->_22, matrix->_23, matrix->_24, matrix->_32, matrix->_33, matrix->_34);
	tempMatrix._24 = determinant3(matrix->_11, matrix->_13, matrix->_14, matrix->_21, matrix->_23, matrix->_24, matrix->_31, matrix->_33, matrix->_34);
	tempMatrix._34 = -determinant3(matrix->_11, matrix->_12, matrix->_14, matrix->_21, matrix->_22, matrix->_24, matrix->_31, matrix->_32, matrix->_34);
	tempMatrix._44 = determinant3(matrix->_11, matrix->_12, matrix->_13, matrix->_21, matrix->_22, matrix->_23, matrix->_31, matrix->_32, matrix->_33);

	m3dMatrixScale(&tempMatrix, &tempMatrix, 1 / det);
	m3dMatrixCopy(outMatrix, &tempMatrix);

	return outMatrix;
}

m3dMatrix* m3dMatrixMultiply(m3dMatrix* outMatrix, const m3dMatrix* matrix1, const m3dMatrix* matrix2)
{
	m3dMatrix tempMatrix;
	float *matrix1Array, *matrix2Array, *tempMatrixArray;
	int r, i, j;

	tempMatrixArray = &tempMatrix;
	matrix1Array = matrix1;
	matrix2Array = matrix2;

	for (i = 0;i<4;i++)
	{
		for (j = 0;j<4;j++)
		{
			tempMatrixArray[4 * i + j] = 0;
			for (r = 0;r<4;r++)
				tempMatrixArray[4 * i + j] += matrix1Array[4 * i + r] * matrix2Array[4 * r + j];
		}
	}

	m3dMatrixCopy(outMatrix, &tempMatrix);

	return outMatrix;
}

m3dMatrix* m3dMatrixTranspose(m3dMatrix* outMatrix, const m3dMatrix* matrix)
{
	m3dMatrix tempMatrix;
	float *matrixArray, *tempMatrixArray;
	int i, j;

	tempMatrixArray = &tempMatrix;
	matrixArray = matrix;

	for (i = 0; i < 4;i++)
		for (j = 0;j < 4;j++)
			tempMatrixArray[i * 4 + j] = matrixArray[j * 4 + i];

	m3dMatrixCopy(outMatrix, &tempMatrix);

	return outMatrix;
}



m3dMatrix* m3dMatrixAdd(m3dMatrix* outMatrix, const m3dMatrix* matrix1, const m3dMatrix* matrix2)
{
	outMatrix->_11 = matrix1->_11 + matrix2->_11;
	outMatrix->_12 = matrix1->_12 + matrix2->_12;
	outMatrix->_13 = matrix1->_13 + matrix2->_13;
	outMatrix->_14 = matrix1->_14 + matrix2->_14;
	outMatrix->_21 = matrix1->_21 + matrix2->_21;
	outMatrix->_22 = matrix1->_22 + matrix2->_22;
	outMatrix->_23 = matrix1->_23 + matrix2->_23;
	outMatrix->_24 = matrix1->_24 + matrix2->_24;
	outMatrix->_31 = matrix1->_31 + matrix2->_31;
	outMatrix->_32 = matrix1->_32 + matrix2->_32;
	outMatrix->_33 = matrix1->_33 + matrix2->_33;
	outMatrix->_34 = matrix1->_34 + matrix2->_34;
	outMatrix->_41 = matrix1->_41 + matrix2->_41;
	outMatrix->_42 = matrix1->_42 + matrix2->_42;
	outMatrix->_43 = matrix1->_43 + matrix2->_43;
	outMatrix->_44 = matrix1->_44 + matrix2->_44;

	return outMatrix;
}

m3dMatrix* m3dMatrixSub(m3dMatrix* outMatrix, const m3dMatrix* matrix1, const m3dMatrix* matrix2)
{
	outMatrix->_11 = matrix1->_11 - matrix2->_11;
	outMatrix->_12 = matrix1->_12 - matrix2->_12;
	outMatrix->_13 = matrix1->_13 - matrix2->_13;
	outMatrix->_14 = matrix1->_14 - matrix2->_14;
	outMatrix->_21 = matrix1->_21 - matrix2->_21;
	outMatrix->_22 = matrix1->_22 - matrix2->_22;
	outMatrix->_23 = matrix1->_23 - matrix2->_23;
	outMatrix->_24 = matrix1->_24 - matrix2->_24;
	outMatrix->_31 = matrix1->_31 - matrix2->_31;
	outMatrix->_32 = matrix1->_32 - matrix2->_32;
	outMatrix->_33 = matrix1->_33 - matrix2->_33;
	outMatrix->_34 = matrix1->_34 - matrix2->_34;
	outMatrix->_41 = matrix1->_41 - matrix2->_41;
	outMatrix->_42 = matrix1->_42 - matrix2->_42;
	outMatrix->_43 = matrix1->_43 - matrix2->_43;
	outMatrix->_44 = matrix1->_44 - matrix2->_44;

	return outMatrix;
}

m3dMatrix* m3dMatrixIdentity(m3dMatrix* outMatrix)
{
	m3dMatrix identityMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	m3dMatrixCopy(outMatrix, &identityMatrix);

	return outMatrix;
}

m3dMatrix* m3dMatrixOrtho(m3dMatrix* outMatrix, float width, float height, float minZ, float maxZ)
{
	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = 2 / width;
	outMatrix->_22 = 2 / height;
	outMatrix->_33 = 1 / (maxZ - minZ);
	outMatrix->_43 = -minZ / (maxZ - minZ);

	return outMatrix;
}

m3dMatrix* m3dMatrixPerspective(m3dMatrix* outMatrix, float width, float height, float minZ, float maxZ)
{
	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = 2 * minZ / width;
	outMatrix->_22 = 2 * minZ / height;
	outMatrix->_33 = maxZ / (maxZ - minZ);
	outMatrix->_43 = minZ*maxZ / (minZ - maxZ);
	outMatrix->_44 = 0;
	outMatrix->_34 = 1;

	return outMatrix;
}

m3dMatrix* m3dMatrixPerspectiveFov(m3dMatrix* outMatrix, float fov, float aspect, float minZ, float maxZ)
{
	float width, height;


	height = 2 * minZ * tan(fov / 2);
	width = height*aspect;

	return m3dMatrixPerspective(outMatrix, width, height, minZ, maxZ);
}

m3dMatrix* m3dMatrixLookAt(m3dMatrix* outMatrix, const m3dVector3* eye, const m3dVector3* at, const m3dVector3* up)
{
	m3dVector3 xAxis, yAxis, zAxis;

	m3dVec3Normalize(&zAxis, m3dVec3Sub(&zAxis, at, eye));
	m3dVec3Normalize(&xAxis, m3dVec3Cross(&xAxis, up, &zAxis));
	m3dVec3Cross(&yAxis, &zAxis, &xAxis);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = xAxis.x;
	outMatrix->_12 = yAxis.x;
	outMatrix->_13 = zAxis.x;
	outMatrix->_21 = xAxis.y;
	outMatrix->_22 = yAxis.y;
	outMatrix->_23 = zAxis.y;
	outMatrix->_31 = xAxis.z;
	outMatrix->_32 = yAxis.z;
	outMatrix->_33 = zAxis.z;
	outMatrix->_41 = -m3dVec3Dot(&xAxis, eye);
	outMatrix->_42 = -m3dVec3Dot(&yAxis, eye);
	outMatrix->_43 = -m3dVec3Dot(&zAxis, eye);

	return outMatrix;
}

// Rotation
m3dMatrix* m3dMatrixRotationX(m3dMatrix* outMatrix, float angle)
{
	float cs, sn;
	sn = sin(-angle);
	cs = cos(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_22 = cs;
	outMatrix->_23 = -sn;
	outMatrix->_32 = sn;
	outMatrix->_33 = cs;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationY(m3dMatrix* outMatrix, float angle)
{
	float cs, sn;
	sn = sin(-angle);
	cs = cos(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = cs;
	outMatrix->_13 = sn;
	outMatrix->_31 = -sn;
	outMatrix->_33 = cs;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationZ(m3dMatrix* outMatrix, float angle)
{
	float cs, sn;
	sn = sin(-angle);
	cs = cos(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = cs;
	outMatrix->_12 = -sn;
	outMatrix->_21 = sn;
	outMatrix->_22 = cs;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationAxis(m3dMatrix* outMatrix, const m3dVector3* axis, float angle)
{
	float cs, sn, x, y, z;
	m3dVector3 normAxis;
	m3dVec3Normalize(&normAxis, axis);

	x = normAxis.x;
	y = normAxis.y;
	z = normAxis.z;
	sn = sin(-angle);
	cs = cos(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = cs + (1 - cs)*x*x;
	outMatrix->_12 = (1 - cs)*x*y - sn*z;
	outMatrix->_13 = (1 - cs)*x*z + sn*y;

	outMatrix->_21 = (1 - cs)*y*x + sn*z;
	outMatrix->_22 = cs + (1 - cs)*y*y;
	outMatrix->_23 = (1 - cs)*y*z - sn*x;

	outMatrix->_31 = (1 - cs)*z*x - sn*y;
	outMatrix->_32 = (1 - cs)*z*y + sn*x;
	outMatrix->_33 = cs + (1 - cs)*z*z;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationYawPitchRoll(m3dMatrix* outMatrix, float yaw, float pitch, float roll)
{
	m3dMatrix yawMatrix, pitchMatrix, rollMatrix;

	m3dMatrixRotationX(&pitchMatrix, pitch);
	m3dMatrixRotationY(&yawMatrix, yaw);
	m3dMatrixRotationZ(&rollMatrix, roll);

	m3dMatrixMultiply(outMatrix, m3dMatrixMultiply(&rollMatrix, &rollMatrix, &pitchMatrix), &yawMatrix);

	return outMatrix;
}

// Transnform
m3dMatrix* m3dMatrixScaling(m3dMatrix* outMatrix, float x, float y, float z)
{
	m3dMatrixIdentity(outMatrix);
	outMatrix->_11 = x;
	outMatrix->_22 = y;
	outMatrix->_33 = z;

	return  outMatrix;
}

m3dMatrix* m3dMatrixTranslation(m3dMatrix* outMatrix, float x, float y, float z)
{
	m3dMatrixIdentity(outMatrix);
	outMatrix->_41 = x;
	outMatrix->_42 = y;
	outMatrix->_43 = z;

	return  outMatrix;
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
	m3dVector4 transVec = { vec->x, vec->y, vec->z, 1 };

	m3dVec4TransformCoord(&transVec, &transVec, matrix);
	m3dVec4Scale(&transVec, &transVec, 1 / transVec.w);
	m3dVec3Copy(outVec, &transVec);

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


inline float atomicMaxf(volatile __global float *source, const float operand) {
	union {
		unsigned int intVal;
		float floatVal;
	} newVal;
	union {
		unsigned int intVal;
		float floatVal;
	} prevVal;
	do {
		prevVal.floatVal = *source;
		newVal.floatVal = max(prevVal.floatVal, operand);
	} while (atomic_cmpxchg((volatile __global unsigned int *)source, prevVal.intVal, newVal.intVal) != prevVal.intVal);

	return newVal.floatVal;
}

void swap(void** val1, void** val2)
{
	void* temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}




