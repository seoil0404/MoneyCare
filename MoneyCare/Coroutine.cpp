#include "Coroutine.h"
#include "DebugLog.h"

std::queue<std::function<void()>> Coroutine::functionQueue;

void Coroutine::updateFunctions()
{
	int queueSize = functionQueue.size();
	for (int index = 0; index < queueSize; index++)
	{
		functionQueue.front()();
		functionQueue.pop();
	}
}