#pragma once
#include <SFML/Graphics.hpp>
#include "Extentions.h"

class WindowManager
{
public:
	static void Initialize();

	static sf::RenderWindowEx window;
	static sf::Event getEventState() { return eventState; };
	
	// this function should be call every frames to change curser type
	static void ChangeCursorToHand() { is_cursor_on_button = true; };

private:
	static void EventUpdate();
	static void ClearWindow();
	static void DisplayWindow();

	static void CursorStateUpdate();

	static sf::Event eventState;

	static bool is_cursor_on_button;
	static sf::Cursor::Type currentCursorState;

	static sf::Cursor arrowCursor;
	static sf::Cursor handCursor;

	friend int main();
};