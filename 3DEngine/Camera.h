#ifndef CAMERA_H
#define CAMERA_H
#include "Math3d.h"
/// Control of camera

int grCameraInit();

//  Change position and rotation in absolute
int grSetCameraPosition(const m3dVector3* position);
int grSetCameraRotation(const m3dVector3* rotation);

// Change params compare to current params
int grCameraRotate(float yaw, float pitch, float roll);
int grCameraMove(float x, float y, float z);

// Get params
m3dVector3* getCameraRotation(m3dVector3* outVector);
m3dVector3* getCameraPosition(m3dVector3* outVector);
m3dMatrix* grGetViewMatrix(m3dMatrix* outMatrix);


#endif