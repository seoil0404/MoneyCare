#pragma once
#include "Coroutine.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include "RenderWindowEx.h"
#include "ApplicationManager.h"
#include "Global.h"
#include <string>

class WindowManager
{
public:
	static void Update(const std::queue<sf::Drawable*>&);

	//static sf::RenderWindowEx& getWindowRef() { return window; };
	static sf::Event getEventState() { return eventState; };

private:
	static void EventUpdate();
	static void ClearWindow();
	static void DisplayWindow();

	static sf::RenderWindowEx window;
	static sf::Event eventState;

	friend int main();
};