#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

/// Logging in program

// Open log file
int logInit();
// Make log
int log(const char* text);
// Close log file
int logShutdown();

#endif