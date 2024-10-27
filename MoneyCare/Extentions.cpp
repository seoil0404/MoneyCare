#include "Extentions.h"
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"

// RenderWindowEx -----------------------------------------------------------------------------------------------------

sf::RenderWindowEx::RenderWindowEx(
    sf::VideoMode _VideoMode, std::string _ScreenName, sf::Uint32 style)
    : RenderWindow(_VideoMode, _ScreenName, style)
{
    setScreenRatio(SCREEN_RATIO_X, SCREEN_RATIO_Y);
    Debug::Log("DEBUG: RenderWindowEx spawned");
};

void sf::RenderWindowEx::setScreenRatio(int ratioX, int ratioY)
{
    sf::FloatRect floatRect(0, 0, (float)ratioX, (float)ratioY);

    sf::View view(floatRect);

    RenderWindow::setView(view);
}

// RectangleShapeEx -----------------------------------------------------------------------------------------------------

std::shared_ptr<sf::RectangleShapeEx> sf::RectangleShapeEx::Create(sf::Vector2f size)
{
    std::shared_ptr<sf::RectangleShapeEx> tempObject(new RectangleShapeEx(size));
    
    tempObject->UpdateObject();

    return tempObject;
}

sf::RectangleShapeEx::RectangleShapeEx(sf::Vector2f size) : sf::RectangleShape(size)
{
    // set origin to middle of the object
    this->setOrigin(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2));
}

void sf::RectangleShapeEx::UpdateObject()
{
    WindowManager::window.draw(*this);

    Debug::Log("DEBUG: Object has been updated");
    
    Coroutine::SafeAddCoroutine(static_cast<std::weak_ptr<sf::RectangleShapeEx>>(shared_from_this()), std::bind(&sf::RectangleShapeEx::UpdateObject, this));
}