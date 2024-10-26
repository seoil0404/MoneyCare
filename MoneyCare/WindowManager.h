#pragma once
#include <SFML/Graphics.hpp>
#include "Extentions.h"

class WindowManager
{
public:
	static sf::RenderWindowEx window;
	static sf::Event getEventState() { return eventState; };

private:
	static void EventUpdate();
	static void ClearWindow();
	static void DisplayWindow();

	static sf::Event eventState;

	friend int main();
};