#include "WindowManager.h"
#include "Coroutine.h"
#include "ApplicationManager.h"
#include "DebugLog.h"
#include <string>

sf::RenderWindowEx WindowManager::window;
sf::Event WindowManager::eventState;

bool WindowManager::is_cursor_on_button;

sf::Cursor WindowManager::arrowCursor;
sf::Cursor WindowManager::handCursor;

sf::Cursor::Type WindowManager::currentCursorState;

std::shared_ptr<sf::TextEx> WindowManager::inputField;
std::shared_ptr<sf::TextEx> WindowManager::inputDigitField;

std::function<void()> WindowManager::upScroll;
std::function<void()> WindowManager::downScroll;

void WindowManager::Initialize()
{
	is_cursor_on_button = false;

	arrowCursor.loadFromSystem(sf::Cursor::Arrow);
	handCursor.loadFromSystem(sf::Cursor::Hand);

	currentCursorState = sf::Cursor::Arrow;

	upScroll = [&]() {};
	downScroll = [&]() {};
}

void WindowManager::EventUpdate()
{
	// turn to empty value
	eventState.type = sf::Event::Count;
	
	while ((window.pollEvent(eventState)))
	{
		if (eventState.type == sf::Event::Closed)
		{
			Debug::Log("DEBUG: Event::Closed has been called");

			window.close();
			ApplicationManager::Quit();
		}

		if (eventState.type == sf::Event::KeyPressed)
		{
			if (eventState.key.code == sf::Keyboard::BackSpace)
			{
				if (inputField != nullptr && inputField->getString().getSize() > 0)
				{
					std::string currentStr = inputField->getString();
					currentStr.pop_back();
					inputField->setString(currentStr);
				}
				else if (inputDigitField != nullptr && inputDigitField->getString().getSize() > 0)
				{
					std::string currentStr = inputDigitField->getString();
					currentStr.pop_back();
					inputDigitField->setString(currentStr);
				}
			}
			else if (eventState.key.code == sf::Keyboard::Space)
			{
				if (inputField != nullptr)
				{
					inputField->setString(inputField->getString() + " ");
				}
			}
		}
		
		if (eventState.type == sf::Event::TextEntered)
		{
			if (eventState.text.unicode >= 33 && eventState.text.unicode <= 126)
			{
				char currentKey = static_cast<char>(eventState.text.unicode);

				if (inputField != nullptr)
				{
					inputField->setString(inputField->getString() + currentKey);
				}
				else if (eventState.text.unicode >= 48 && eventState.text.unicode <= 57 && inputDigitField != nullptr)
				{
					inputDigitField->setString(inputDigitField->getString() + currentKey);
				}

			}
		}
		

		if (eventState.type == sf::Event::MouseWheelScrolled && eventState.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
		{
			if (eventState.mouseWheelScroll.delta > 0) upScroll();
			else downScroll();
		}
	}

	CursorStateUpdate();

	//Debug::Log("DEBUG: EventUpdate function has been executed");

	Coroutine::AddCoroutine(
		[&]() {
			EventUpdate();
		}
	);
}

void WindowManager::ClearWindow()
{
	window.clear(sf::Color::White);

	//Debug::Log("DEBUG: ClearWindow function has been executed");

	Coroutine::AddCoroutine(
		[&]() {
			ClearWindow();
		}
	);
}

void WindowManager::DisplayWindow()
{
	window.display();

	//Debug::Log("DEBUG: DisplayWindow function has been executed");

	Coroutine::AddCoroutine(
		[&]() {
			DisplayWindow();
		}
	);
}

void WindowManager::CursorStateUpdate()
{
	if (is_cursor_on_button)
	{
		is_cursor_on_button = false;
		if (currentCursorState != sf::Cursor::Type::Hand)
		{
			window.setMouseCursor(handCursor);
			currentCursorState = sf::Cursor::Type::Hand;
		}
	}
	else if(currentCursorState != sf::Cursor::Type::Arrow)
	{
		window.setMouseCursor(arrowCursor);
		currentCursorState = sf::Cursor::Type::Arrow;
	}
}

void WindowManager::setInputField(std::shared_ptr<sf::TextEx> text)
{
	inputField = text;
	inputDigitField = nullptr;
}

void WindowManager::setInputDigitField(std::shared_ptr<sf::TextEx> text)
{
	inputField = nullptr;
	inputDigitField = text;
}

void WindowManager::setUpScrollEvent(std::function<void()> func)
{
	upScroll = func;
}

void WindowManager::setDownScrollEvent(std::function<void()> func)
{
	downScroll = func;
}