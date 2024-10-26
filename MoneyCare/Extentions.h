#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

namespace sf
{
	const int SCREEN_RATIO_X = 1600;
	const int SCREEN_RATIO_Y = 900;

	class RenderWindowEx : public sf::RenderWindow
	{
	public:
		RenderWindowEx(
			sf::VideoMode _VideoMode = sf::VideoMode::getDesktopMode(),
			std::string _ScreenName = "MoneyCare",
			sf::Uint32 style = sf::Style::Default);
		void setScreenRatio(int, int);
	};

	// Drawable Extentions -----------------------------------------------------------------------------------------------------

	class RectangleShapeEx : public sf::RectangleShape
	{
	public:
		static RectangleShapeEx* Create(sf::Vector2f);
		void Destroy() { needDestroy = true; };

		void UpdateObject();

	private:
		RectangleShapeEx(sf::Vector2f);
		~RectangleShapeEx() {};

		bool needDestroy;

		
		void SafeCheckDelete();
	};
}

