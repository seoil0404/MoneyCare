#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <memory>
#include <functional>

namespace sf
{
	const int SCREEN_RATIO_X = 1600;
	const int SCREEN_RATIO_Y = 900;

	const int FRAME_LIMIT = 144;

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

	// This class should be created using dynamic allocation with shared_ptr.
	class RectangleShapeEx : public sf::RectangleShape, public std::enable_shared_from_this<RectangleShapeEx>
	{
	public:
		static std::shared_ptr<RectangleShapeEx> Create(sf::Vector2f, sf::Vector2f = sf::Vector2f(0, 0));

		~RectangleShapeEx() {};

		// this function process with an animation
		void Translate(sf::Vector2f, float);
		// this function process with an animation
		void Resize(sf::Vector2f, float);
	
		const float MAX_ANIMATION_SPEED_RATE = 100;

	protected:
		RectangleShapeEx(sf::Vector2f, sf::Vector2f);

		void UpdateAnimation();

		virtual void UpdateObject();

	private:
		sf::Vector2f position_animation;
		float position_animation_speed_rate;

		sf::Vector2f scale_animation;
		float scale_animation_speed_rate;

		void UpdatePositionAnimation();
		void UpdateScaleAnimation();
	};

	class ButtonShape : public RectangleShapeEx
	{
	public:
		static std::shared_ptr<ButtonShape> Create(std::function<void()>, sf::Vector2f, sf::Vector2f = sf::Vector2f(0, 0));
		
		~ButtonShape() {};

	private:
		ButtonShape(sf::Vector2f, sf::Vector2f);
		
	};
}

