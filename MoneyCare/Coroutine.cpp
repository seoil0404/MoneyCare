#include "Coroutine.h"

std::queue<std::function<void()>> Coroutine::functionQueue;

void Coroutine::processFunctions()
{
	int queueSize = functionQueue.size();
	for (int index = 0; index < queueSize; index++)
	{
		functionQueue.front()();
		functionQueue.pop();
	}
}