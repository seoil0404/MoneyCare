#include "Extentions.h"
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"
#include "Global.h"

std::shared_ptr<sf::ButtonShape> sf::ButtonShape::Create(sf::Vector2f size, sf::Vector2f position)
{
	std::shared_ptr<sf::ButtonShape> tempObject(new ButtonShape(size, position));

	tempObject->UpdateObject();

	return tempObject;
}

sf::ButtonShape::ButtonShape(sf::Vector2f size, sf::Vector2f position) : RectangleShapeEx(size, position)
{
	isHovering = false;
	isClicked = false;

	click_EventFunction = []() {};
	exitClick_EventFunctiom = []() {};
	enter_EventFunction = []() {};
	exit_EventFunction = []() {};
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
		if (isHovering == false)
		{
			isHovering = true;
			enter_EventFunction();
		}

		if (WindowManager::getEventState().type == sf::Event::MouseButtonPressed)
		{
			isClicked = true;
			click_EventFunction();
		}
	}
	else if (isHovering == true)
	{
		isHovering = false;
		exit_EventFunction();
	}

	bool flag1 = WindowManager::getEventState().type == sf::Event::MouseButtonPressed;
	bool flag2 = !getGlobalBounds().contains(mousePos);
	bool flag3 = isClicked == true;

	if (flag1 && flag2 && flag3)
	{
		isClicked = false;
		exitClick_EventFunctiom();
	}
}

void sf::ButtonShape::setClickEvent(std::function<void()> func)
{
	click_EventFunction = func;
}

void sf::ButtonShape::setEnterEvent(std::function<void()> func)
{
	enter_EventFunction = func;
}

void sf::ButtonShape::setExitEvent(std::function<void()> func)
{
	exit_EventFunction = func;
}

void sf::ButtonShape::setExitClickEvent(std::function<void()> func)
{
	exitClick_EventFunctiom = func;
}