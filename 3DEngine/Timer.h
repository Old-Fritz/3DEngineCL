
#ifndef TIMER_H
#define TIMER_H

/// Control by all program systems and render cycle

// Initialize and start timer
int tmInit();
// change frame time
void tmFrame();
// Get last frame time in seconds
float tmFrameTime();

#endif