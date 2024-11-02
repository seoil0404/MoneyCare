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
			sf::Texture Add;
			sf::Texture AddItem;
			sf::Texture AddLayer;
			sf::Texture Input;
			sf::Texture PositiveItem;
			sf::Texture NegativeItem;
			sf::Texture Delete;
			sf::Texture LayerLine;
		};
		struct ViewType
		{

		};
		struct CategoryType
		{
			sf::Texture Item;
			sf::Texture Input;
			sf::Texture Add;
			sf::Texture Delete;
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
