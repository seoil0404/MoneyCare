#pragma once
#include <functional>
#include <queue>
#include <memory>

class Coroutine
{
public:
	// Loop functions are run in this queue
	template<typename... Arguments>
	static void AddCoroutine(std::function<void(Arguments...)> functions, Arguments&&...arguments)
	{
		functionQueue.push(std::bind(functions, arguments...));
	}

	static void AddCoroutine(std::function<void()> functions)
	{
		functionQueue.push(functions);
	}

	template<typename WeakPtr, typename... Arguments>
	static void SafeAddCoroutine(std::weak_ptr<WeakPtr> weakPtr, std::function<void(Arguments...)> functions, Arguments&&... arguments)
	{
		functionQueue.push(std::bind(functions, arguments...));
		//Coroutine::AddCoroutine(std::bind(&Coroutine::RemoveIfNotExist, this), weakPtr);
		//functionQueue.push(std::bind(functions, arguments...));
	}

	template<typename WeakPtr, typename... Arguments>
	static void SafeAddCoroutine(std::weak_ptr<WeakPtr> weakPtr, std::function<void()> functions)
	{
		functionQueue.push(functions);
		//Coroutine::AddCoroutine(std::bind(&Coroutine::RemoveIfNotExist, this), weakPtr);
		//functionQueue.push(functions);
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

