#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

namespace sf
{
	class RenderWindowEx : public sf::RenderWindow
	{
	public:
		// This constructor automatically detects the screen size and opens the window in fullscreen mode.
		RenderWindowEx();
		RenderWindowEx(sf::VideoMode _VideoMode, std::string _ScreenName) : RenderWindow(_VideoMode, _ScreenName) {};
		void draw(std::queue<sf::Drawable*>);
	};
}

