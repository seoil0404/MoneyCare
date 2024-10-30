#include "WindowManager.h"
#include "Coroutine.h"
#include "ApplicationManager.h"
#include "DebugLog.h"

sf::RenderWindowEx WindowManager::window;
sf::Event WindowManager::eventState;

bool WindowManager::is_cursor_on_button;

sf::Cursor WindowManager::arrowCursor;
sf::Cursor WindowManager::handCursor;

sf::Cursor::Type WindowManager::currentCursorState;

void WindowManager::Initialize()
{
	is_cursor_on_button = false;

	arrowCursor.loadFromSystem(sf::Cursor::Arrow);
	handCursor.loadFromSystem(sf::Cursor::Hand);

	currentCursorState = sf::Cursor::Arrow;
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
