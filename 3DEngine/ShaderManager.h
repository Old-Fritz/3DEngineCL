#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

/// United control of creating and releasing all shaders

// Initialize all shaders
int grCreateAllShaders();
// Release all resources connected with shaders
void grShutdownAllShaders();
// Execute all shaders
int grExecuteAllShaders();

#endif