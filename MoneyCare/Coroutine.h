#pragma once
#include <functional>
#include <queue>
#include <memory>

class Coroutine
{
public:
	// Loop functions are run in this queue
	static void AddCoroutine(std::function<void()> functions)
	{
		functionQueue.push(functions);
	}

	template<typename WeakPtr, typename... Arguments>
	static void SafeAddCoroutine(std::weak_ptr<WeakPtr> weakPtr, std::function<void()> functions)
	{
		functionQueue.push(
			[=]() {
				Coroutine::RemoveIfNotExist(weakPtr);
			}
		);
		functionQueue.push(functions);
	}
	

private:
	static void updateFunctions();

	static std::queue<std::function<void()>> functionQueue;
	
	template<typename WeakPtr>
	static void	RemoveIfNotExist(std::weak_ptr<WeakPtr> weakPtr)
	{
		if (weakPtr.expired()) functionQueue.pop();
	}
	
	
	friend int main();
};

