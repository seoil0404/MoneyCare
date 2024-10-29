#include "Extentions.h"
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"
#include "Global.h"

std::shared_ptr<sf::ButtonShape> sf::ButtonShape::Create(std::function<void()> _eventFunction, sf::Vector2f size, sf::Vector2f position)
{
	std::shared_ptr<sf::ButtonShape> tempObject(new ButtonShape(_eventFunction, size, position));

	tempObject->UpdateObject();

	return tempObject;
}

sf::ButtonShape::ButtonShape(std::function<void()> _eventFunction, sf::Vector2f size, sf::Vector2f position) : RectangleShapeEx(size, position)
{
	eventFunction = _eventFunction;
}

void sf::ButtonShape::UpdateObject()
{
	CatchEvent();
	UpdateAnimation();

	WindowManager::window.draw(*this);

	Coroutine::SafeAddCoroutine(
		get_weak(this),
		[&]() {UpdateObject();}
	);
}

void sf::ButtonShape::CatchEvent()
{
	sf::Vector2f mousePos = WindowManager::window.mapPixelToCoords(sf::Mouse::getPosition(WindowManager::window));

	if (getGlobalBounds().contains(mousePos))
	{
		WindowManager::ChangeCursorToHand();

		if (WindowManager::getEventState().type == sf::Event::MouseButtonPressed) {
			eventFunction();
		}
	}
}