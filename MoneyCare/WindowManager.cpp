#include "WindowManager.h"

sf::RenderWindowEx WindowManager::window;
sf::Event WindowManager::eventState;

void WindowManager::Update(const std::queue<sf::Drawable*>& objectQueue)
{
	window.draw(objectQueue);
}

void WindowManager::EventUpdate()
{
	while ((window.pollEvent(eventState)))
	{
		if (eventState.type == sf::Event::Closed)
		{
			Debug::Log("DEBUG: Event::Closed has been called");
			window.close();
			ApplicationManager::Quit();
		}
	}
	
	//Debug::Log("DEBUG: EventUpdate function has been executed");
	
	Coroutine::AddCoroutine(EventUpdate);
}

void WindowManager::ClearWindow()
{
	window.clear();
	
	//Debug::Log("DEBUG: ClearWindow function has been executed");

	Coroutine::AddCoroutine(ClearWindow);
}

void WindowManager::DisplayWindow()
{
	window.display();

	//Debug::Log("DEBUG: DisplayWindow function has been executed");

	Coroutine::AddCoroutine(DisplayWindow);
}