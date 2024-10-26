#include "DebugLog.h"

void Debug::Log(std::string _log)
{
	#ifdef DEBUG
		printf(_log.c_str());
		printf("\n");
	#endif
}