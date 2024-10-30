#pragma once
#include <SFML/Graphics.hpp>

namespace sf
{
	class FontManager
	{
	public:
		static void Initialize();
		
		static sf::Font Black;
		static sf::Font Bold;
		static sf::Font ExtraBold;
		static sf::Font ExtraLight;
		static sf::Font Light;
		static sf::Font Medium;
		static sf::Font Regular;
		static sf::Font SemiBold;
		static sf::Font Thin;
	};

	class TextureManager
	{
	private:
		struct AddType
		{

		};
		struct ViewType
		{

		};
		struct CategoryType
		{
			sf::Texture item;
		};
		struct BudgetType
		{

		};

	public:
		static void Initialize();

		static AddType Add;
		static ViewType View;
		static CategoryType Category;
		static BudgetType Budget;
	};
}
