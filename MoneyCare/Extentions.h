#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <memory>

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

	class Animationable
	{
	public:
		virtual void MoveWithAnimation(sf::Vector2f) = 0;
		virtual void ResizeWithAnimation(sf::Vector2f) = 0;
	};

	// This class should be created using dynamic allocation and must be destroyed through user-defined functions only.
	class RectangleShapeEx : public sf::RectangleShape, public std::enable_shared_from_this<RectangleShapeEx>
	{
	public:
		static std::shared_ptr<RectangleShapeEx> Create(sf::Vector2f);
		~RectangleShapeEx() {};
		RectangleShapeEx(sf::Vector2f);
	private:
		

		void UpdateObject();
	};

	
}

