#ifndef PARTICLES_SYSTEM_H
#define PARTICLES_SYSTEM_H
#include "BaseModel.h"

typedef struct mdParticleVertex
{
	m3dVector3 position;
	m3dVector3 speed;
} mdParticleVertex;

typedef struct mdParticlesSystem
{
	mdBaseModel model;
} mdParticlesSystem;

int mdParticlesSystemCreate(mdParticlesSystem* model, int count);
void mdParticlesSystemShutdown(mdParticlesSystem* model);

#endif