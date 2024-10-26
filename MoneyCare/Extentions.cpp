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
    sf::FloatRect floatRect(0, 0, ratioX, ratioY);

    sf::View view(floatRect);

    RenderWindow::setView(view);
}

// RectangleShapeEx -----------------------------------------------------------------------------------------------------

sf::RectangleShapeEx* sf::RectangleShapeEx::Create(sf::Vector2f transform)
{
    return new sf::RectangleShapeEx(transform);
}

sf::RectangleShapeEx::RectangleShapeEx(sf::Vector2f transform) : sf::RectangleShape(transform), needDestroy(false)
{
    UpdateObject();
}

void sf::RectangleShapeEx::UpdateObject()
{
    SafeCheckDelete();

    WindowManager::window.draw(*this);
    
    Coroutine::AddCoroutine(&RectangleShapeEx::UpdateObject, this);
}

void sf::RectangleShapeEx::SafeCheckDelete()
{
    if (needDestroy) {
        delete this;
    }
}