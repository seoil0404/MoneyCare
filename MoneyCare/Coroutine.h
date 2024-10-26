#pragma once
#include <functional>
#include <queue>
#include "DebugLog.h"

class Coroutine
{
public:
	// Loop functions are run in this queue
	template<typename Function, typename... Arguments>
	static void AddCoroutine(Function&& function, Arguments&&...arguments)
	{
		functionQueue.push(std::bind(std::forward<Function>(function), std::forward<Arguments>(arguments)...));
	}

private:
	static void updateFunctions();

	static std::queue<std::function<void()>> functionQueue;
	
	
	friend int main();
};

