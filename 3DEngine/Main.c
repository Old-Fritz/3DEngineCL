#include "System.h"

int main()
{
	int result;

	result = sysInit();
	if(!result)
		return 0;

	sysRun();
	sysShutdown();


	return 0;
}