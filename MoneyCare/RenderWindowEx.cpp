#include "RenderWindowEx.h"

sf::RenderWindowEx::RenderWindowEx() : sf::RenderWindow(sf::VideoMode::getDesktopMode(), "MoneyCare", sf::Style::Default)
{
    
}

void sf::RenderWindowEx::draw(std::queue<sf::Drawable*> drawQueue)
{
    while (!drawQueue.empty())
    {
        sf::Drawable* drawable = drawQueue.front();

        sf::RenderWindow::draw(*drawable);
        
        drawQueue.pop();
    }
}