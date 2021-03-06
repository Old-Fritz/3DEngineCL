#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#include "SimpleShader.h"
#include "ColorShader.h"
#include "LightShader.h"
#include "ParticlesShader.h"
/// United control of creating and releasing all shaders

// Initialize all shaders
int grCreateAllShaders();
// Release all resources connected with shaders
void grShutdownAllShaders();
// Execute all shaders
int grExecuteAllShaders();
// Wait for finish all shaders
int grFinishAllShaders();

#endif