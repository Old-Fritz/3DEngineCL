#ifndef LS_LM_RENDERER_H
#define LS_LM_RENDERER_H
#include "LightModel.h"
#include "DiffuseLight.h"

/// Class for render simple model with simple shader

int renderLSLM(mdLightModel* lightModel, mdDiffuseLight* light);

#endif