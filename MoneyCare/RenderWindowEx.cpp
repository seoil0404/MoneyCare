#include "Extentions.h"
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"
#include "Global.h"

sf::RenderWindowEx::RenderWindowEx(
    sf::VideoMode _VideoMode, std::string _ScreenName, sf::Uint32 style)
    : RenderWindow(_VideoMode, _ScreenName, style)
{
    setScreenRatio(SCREEN_RATIO_X, SCREEN_RATIO_Y);
    setFramerateLimit(FRAME_LIMIT);

    Debug::Log("DEBUG: RenderWindowEx spawned");
};

void sf::RenderWindowEx::setScreenRatio(int ratioX, int ratioY)
{
    sf::FloatRect floatRect(0, 0, (float)ratioX, (float)ratioY);

    sf::View view(floatRect);

    RenderWindow::setView(view);
}