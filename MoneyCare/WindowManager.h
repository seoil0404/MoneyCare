#pragma once
#include <SFML/Graphics.hpp>
#include "Extentions.h"

class WindowManager
{
public:
	static void Initialize();

	static sf::RenderWindowEx window;
	static sf::Event getEventState() { return eventState; };

	static void setInputField(std::shared_ptr<sf::TextEx>);
	static void setInputDigitField(std::shared_ptr<sf::TextEx>);

	static void setUpScrollEvent(std::function<void()>);
	static void setDownScrollEvent(std::function<void()>);
	
	// this function should be call every frames to change curser type
	static void ChangeCursorToHand() { is_cursor_on_button = true; };

private:
	static void EventUpdate();
	static void ClearWindow();
	static void DisplayWindow();

	static void CursorStateUpdate();

	static std::function<void()> upScroll;
	static std::function<void()> downScroll;

	static sf::Event eventState;

	static bool is_cursor_on_button;
	static sf::Cursor::Type currentCursorState;

	static sf::Cursor arrowCursor;
	static sf::Cursor handCursor;

	static std::shared_ptr<sf::TextEx> inputField;
	static std::shared_ptr<sf::TextEx> inputDigitField;

	friend int main();
};