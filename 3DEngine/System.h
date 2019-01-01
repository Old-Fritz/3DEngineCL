#ifndef SYSTEM_H
#define SYSTEM_H

/// Control by all program systems and render cycle

// Initialize all systems
int sysInit();
// Run render cycle
int sysRun();
// Release all resources
int sysShutdown();

#endif
