#ifndef GRAPHIC_H
#define GRAPHIC_H

/// Control of all graphic resources

// create all graphic components
int grInit();
// function that must be executed every frame
int grFrame();
// release all graphic resources
void grShutdown();

#endif