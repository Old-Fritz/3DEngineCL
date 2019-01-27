#include "Camera.h"

static m3dVector3 camPosition;
static m3dVector3 camRotation;
static m3dMatrix viewMatrix;

static void calculateViewMatrix()
{
	m3dVector3 up, lookAt;
	float yaw, pitch, roll;
	m3dMatrix rotationMatrix;

	// Set vector that points upwards
	up.x = 0;
	up.y = 1;
	up.z = 0;

	// Set default look at of camera
	lookAt.x = 0;
	lookAt.y = 0;
	lookAt.z = 1;

	// Set yaw pitch roll in radians and create rotation matrix
	pitch = camRotation.x;
	yaw = camRotation.y;
	roll = camRotation.z;
	m3dMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Rotate up and lookAt
	m3dVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	m3dVec3TransformCoord(&up, &up, &rotationMatrix);

	// translate look at vector
	m3dVec3Add(&lookAt, &lookAt, &camPosition);

	// create view matrix
	m3dMatrixLookAt(&viewMatrix, &camPosition, &lookAt, &up);
}

int grCameraInit()
{
	camPosition.x = camPosition.y = camPosition.z = 0;
	camRotation.x = camRotation.y = camRotation.z = 0;

	calculateViewMatrix();

	return 1;
}

//  Change position and rotation in absolute
void grSetCameraPosition(const m3dVector3* position)
{
	m3dVec3Copy(&camPosition, position);
	calculateViewMatrix();
}
void grSetCameraRotation(const m3dVector3* rotation)
{
	m3dVec3Copy(&camRotation, rotation);
	calculateViewMatrix();
}

// Change params compare to current params
void grCameraRotate(float yaw, float pitch, float roll)
{
	m3dVector3 rotateVector = { pitch,yaw, roll };

	m3dVec3Add(&camRotation, &camRotation, &rotateVector);
	calculateViewMatrix();
}
void grCameraMove(float x, float y, float z)
{
	m3dVector3 moveVector = { x,y,z };

	m3dVec3Add(&camPosition, &camPosition, &moveVector);
	calculateViewMatrix();
}

// Get params
m3dVector3* getCameraRotation(m3dVector3* outVector)
{
	return m3dVec3Copy(outVector, &camRotation);
}
m3dVector3* getCameraPosition(m3dVector3* outVector)
{
	return m3dVec3Copy(outVector, &camPosition);
}
m3dMatrix* grGetViewMatrix(m3dMatrix* outMatrix)
{
	return m3dMatrixCopy(outMatrix, &viewMatrix);
}