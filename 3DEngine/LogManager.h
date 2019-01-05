#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

/// Logging in program

// Open log file
int logInit();
// Make log
int log(const char* text);
int logNum(double number);
// Close log file
void logShutdown();

#endif