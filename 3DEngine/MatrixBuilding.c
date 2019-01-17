#include "Matrix.h"
#include "math.h"

static m3dMatrix identityMatrix = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };

m3dMatrix* m3dMatrixIdentity(m3dMatrix* outMatrix)
{
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

	outMatrix->_11 = 2*minZ / width;
	outMatrix->_22 = 2*minZ / height;
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
	float cos, sin;
	sin = sinf(-angle);
	cos = cosf(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_22 = cos;
	outMatrix->_23 = -sin;
	outMatrix->_32 = sin;
	outMatrix->_33 = cos;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationY(m3dMatrix* outMatrix, float angle)
{
	float cos, sin;
	sin = sinf(-angle);
	cos = cosf(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = cos;
	outMatrix->_13 = sin;
	outMatrix->_31 = -sin;
	outMatrix->_33 = cos;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationZ(m3dMatrix* outMatrix, float angle)
{
	float cos, sin;
	sin = sinf(-angle);
	cos = cosf(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = cos;
	outMatrix->_12 = -sin;
	outMatrix->_21 = sin;
	outMatrix->_22 = cos;

	return outMatrix;
}

m3dMatrix* m3dMatrixRotationAxis(m3dMatrix* outMatrix, const m3dVector3* axis, float angle)
{
	float cos, sin, x, y, z;
	m3dVector3 normAxis;
	m3dVec3Normalize(&normAxis, axis);

	x = normAxis.x;
	y = normAxis.y;
	z = normAxis.z;
	sin = sinf(-angle);
	cos = cosf(-angle);

	m3dMatrixIdentity(outMatrix);

	outMatrix->_11 = cos + (1 - cos)*x*x;
	outMatrix->_12 = (1 - cos)*x*y - sin*z;
	outMatrix->_13 = (1 - cos)*x*z + sin*y;

	outMatrix->_21 = (1 - cos)*y*x + sin*z;
	outMatrix->_22 = cos + (1 - cos)*y*y;
	outMatrix->_23 = (1 - cos)*y*z - sin*x;

	outMatrix->_31 = (1 - cos)*z*x - sin*y;
	outMatrix->_32 = (1 - cos)*z*y + sin*x;
	outMatrix->_33 = cos + (1 - cos)*z*z;

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

