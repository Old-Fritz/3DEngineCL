#include "Matrix.h"

static float determinant3(float _11, float _12, float _13,
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
	
m3dMatrix* m3dMatrixInverse(m3dMatrix* outMatrix, const m3dMatrix* matrix)
{	
	m3dMatrix tempMatrix;
	float det = m3dMatrixDeterminant(matrix);
	if(!det)
	{
		m3dMatrixCopy(outMatrix, matrix);
		return outMatrix;
	}

	tempMatrix._11 = determinant3(matrix->_22,matrix->_23,matrix->_24,matrix->_32,matrix->_33,matrix->_34,matrix->_42,matrix->_43,matrix->_44);
	tempMatrix._21 = -determinant3(matrix->_21,matrix->_23,matrix->_24,matrix->_31,matrix->_33,matrix->_34,matrix->_41,matrix->_43,matrix->_44);
	tempMatrix._31 = determinant3(matrix->_21,matrix->_22,matrix->_24,matrix->_31,matrix->_32,matrix->_34,matrix->_41,matrix->_42,matrix->_44);
	tempMatrix._41 = -determinant3(matrix->_21,matrix->_22,matrix->_23,matrix->_31,matrix->_32,matrix->_33,matrix->_41,matrix->_42,matrix->_43);
	tempMatrix._12 = -determinant3(matrix->_12,matrix->_13,matrix->_14,matrix->_32,matrix->_33,matrix->_34,matrix->_42,matrix->_43,matrix->_44);
	tempMatrix._22 = determinant3(matrix->_11,matrix->_13,matrix->_14,matrix->_31,matrix->_33,matrix->_34,matrix->_41,matrix->_43,matrix->_44);
	tempMatrix._32 = -determinant3(matrix->_11,matrix->_12,matrix->_14,matrix->_31,matrix->_32,matrix->_34,matrix->_41,matrix->_42,matrix->_44);
	tempMatrix._42 = determinant3(matrix->_11,matrix->_12,matrix->_13,matrix->_31,matrix->_32,matrix->_33,matrix->_41,matrix->_42,matrix->_43);
	tempMatrix._13 = determinant3(matrix->_12,matrix->_13,matrix->_14,matrix->_22,matrix->_23,matrix->_24,matrix->_42,matrix->_43,matrix->_44);
	tempMatrix._23 = -determinant3(matrix->_11,matrix->_13,matrix->_14,matrix->_21,matrix->_23,matrix->_24,matrix->_41,matrix->_43,matrix->_44);
	tempMatrix._33 = determinant3(matrix->_11,matrix->_12,matrix->_14,matrix->_21,matrix->_22,matrix->_24,matrix->_41,matrix->_42,matrix->_44);
	tempMatrix._43 = -determinant3(matrix->_11,matrix->_12,matrix->_13,matrix->_21,matrix->_22,matrix->_23,matrix->_41,matrix->_42,matrix->_43);
	tempMatrix._14 = -determinant3(matrix->_12,matrix->_13,matrix->_14,matrix->_22,matrix->_23,matrix->_24,matrix->_32,matrix->_33,matrix->_34);
	tempMatrix._24 = determinant3(matrix->_11,matrix->_13,matrix->_14,matrix->_21,matrix->_23,matrix->_24,matrix->_31,matrix->_33,matrix->_34);
	tempMatrix._34 = -determinant3(matrix->_11,matrix->_12,matrix->_14,matrix->_21,matrix->_22,matrix->_24,matrix->_31,matrix->_32,matrix->_34);
	tempMatrix._44 = determinant3(matrix->_11,matrix->_12,matrix->_13,matrix->_21,matrix->_22,matrix->_23,matrix->_31,matrix->_32,matrix->_33);

	m3dMatrixScale(&tempMatrix, &tempMatrix, 1/det);
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

	for(i=0;i<4;i++)
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