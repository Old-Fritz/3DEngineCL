#ifndef SETTINGS_H
#define SETTINGS_H

/// Global program settings

// Load settings from file
int setsInit(const char* filename);
// get screen parameters
int setsGetScreenWidth();
int setsGetScreenHeight();
float setGetFieldOfView();

#endif