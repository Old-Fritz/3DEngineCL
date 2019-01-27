#include <time.h>
#include"Timer.h"

static clock_t lastTime;
static float frameTime;

// Initialize all systems
int tmInit()
{
	lastTime = clock();
	frameTime = 0;
}
// Run render cycle
void tmFrame()
{
	clock_t newTime = clock();
	frameTime = (float)(newTime- lastTime)/CLOCKS_PER_SEC;
	lastTime = newTime;
}
// Release all resources
float tmFrameTime()
{
	return frameTime;
}