#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <memory>
#include <functional>

namespace sf
{
	class RenderWindowEx : public sf::RenderWindow
	{
	public:
		RenderWindowEx(
			sf::VideoMode _VideoMode = sf::VideoMode::getDesktopMode(),
			std::string _ScreenName = "MoneyCare",
			sf::Uint32 style = sf::Style::None);
		void setScreenRatio(int, int);

	private:
		const int SCREEN_RATIO_X = 1600;
		const int SCREEN_RATIO_Y = 900;

		const int FRAME_LIMIT = 144;
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
		template<typename T>
		static std::weak_ptr<T> get_weak(T* object) {
			return static_cast<std::weak_ptr<T>>(std::static_pointer_cast<T>(object->shared_from_this()));
		}
		

		RectangleShapeEx(sf::Vector2f, sf::Vector2f);

		virtual void UpdateAnimation();

		virtual void UpdateObject();

	private:
		sf::Vector2f position_animation;
		float position_animation_speed_rate;

		sf::Vector2f scale_animation;
		float scale_animation_speed_rate;

		void UpdatePositionAnimation();
		void UpdateScaleAnimation();
	};

// Drawable Extentions -----------------------------------------------------------------------------------------------------

	// This class should be created using dynamic allocation with shared_ptr.
	class TextEx : public sf::Text, public std::enable_shared_from_this<TextEx>
	{
	public:
		static std::shared_ptr<TextEx> Create(sf::Font&, std::wstring, unsigned int, sf::Vector2f = sf::Vector2f(0, 0));

		~TextEx() {};

		// this function process with an animation
		void Translate(sf::Vector2f, float);

		const float MAX_ANIMATION_SPEED_RATE = 100;

	protected:
		TextEx(sf::Font&, std::wstring, unsigned int, sf::Vector2f);

		template<typename T>
		static std::weak_ptr<T> get_weak(T* object) {
			return static_cast<std::weak_ptr<T>>(std::static_pointer_cast<T>(object->shared_from_this()));
		}

		virtual void UpdateAnimation();

		virtual void UpdateObject();

	private:
		sf::Vector2f position_animation;
		float position_animation_speed_rate;

		void UpdatePositionAnimation();
	};

// Drawable Extentions -----------------------------------------------------------------------------------------------------

	class ButtonShape : public RectangleShapeEx
	{
	public:
		static std::shared_ptr<ButtonShape> Create(sf::Vector2f, sf::Vector2f = sf::Vector2f(0, 0));
		
		void setClickEvent(std::function<void()>);
		void setEnterEvent(std::function<void()>);
		void setExitEvent(std::function<void()>);

		~ButtonShape() {};

	protected:
		void UpdateObject() override;

	private:
		ButtonShape(sf::Vector2f, sf::Vector2f);

		void CatchEvent();

		bool isHovering;

		std::function<void()> click_EventFunction;
		std::function<void()> enter_EventFunction;
		std::function<void()> exit_EventFunction;

	};
}