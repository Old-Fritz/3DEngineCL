#ifndef WINDOW_H
#define WINDOW_H

/// Control of window and render to screen

// Create window
int winInit(int width, int height);
// Get current screen buffer
int winGetBuffer(void** buffer);
// Swap screen buffers
int winSwapBuffers();
// Render buffer to screen
int winRender();
// Close window and release all resources
void winShutdown();


#endif