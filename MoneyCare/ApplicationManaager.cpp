#include "ApplicationManager.h"
#include "DebugLog.h"

void ApplicationManager::Quit()
{
	Debug::Log("DEBUG: Program has terminated.");

	exit(0);
}