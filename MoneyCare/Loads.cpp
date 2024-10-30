#include "Loads.h"
#include "DebugLog.h"

namespace sf
{
	void FontManager::Initialize()
	{
		Black.loadFromFile("./Asset/Fonts/Black.ttf");
		Bold.loadFromFile("./Asset/Fonts/Bold.ttf");
		ExtraBold.loadFromFile("./Asset/Fonts/ExtraBold.ttf");
		ExtraLight.loadFromFile("./Asset/Fonts/ExtraLight.ttf");
		Light.loadFromFile("./Asset/Fonts/Light.ttf");
		Medium.loadFromFile("./Asset/Fonts/Medium.ttf");
		Regular.loadFromFile("./Asset/Fonts/Regular.ttf");
		SemiBold.loadFromFile("./Asset/Fonts/SemiBold.ttf");
		Thin.loadFromFile("./Asset/Fonts/Thin.ttf");
	}

	Font FontManager::Black;
	Font FontManager::Bold;
	Font FontManager::ExtraBold;
	Font FontManager::ExtraLight;
	Font FontManager::Light;
	Font FontManager::Medium;
	Font FontManager::Regular;
	Font FontManager::SemiBold;
	Font FontManager::Thin;

	void TextureManager::Initialize()
	{
		Category.item.loadFromFile("./Asset/Images/Category/item.png");
	}

	TextureManager::AddType TextureManager::Add;
	TextureManager::ViewType TextureManager::View;
	TextureManager::CategoryType TextureManager::Category;
	TextureManager::BudgetType TextureManager::Budget;
}