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
		Add.Add.loadFromFile("./Asset/Images/Add/Add.png");
		Add.AddItem.loadFromFile("./Asset/Images/Add/AddItem.png");
		Add.AddLayer.loadFromFile("./Asset/Images/Add/AddLayer.png");
		Add.Input.loadFromFile("./Asset/Images/Add/Input.png");
		Add.PositiveItem.loadFromFile("./Asset/Images/Add/PositiveItem.png");
		Add.NegativeItem.loadFromFile("./Asset/Images/Add/NegativeItem.png");
		Add.Delete.loadFromFile("./Asset/Images/Add/Delete.png");
		Add.LayerLine.loadFromFile("./Asset/Images/Add/LayerLine.png");

		Category.Item.loadFromFile("./Asset/Images/Category/Item.png");
		Category.Input.loadFromFile("./Asset/Images/Category/Input.png");
		Category.Add.loadFromFile("./Asset/Images/Category/Add.png");
		Category.Delete.loadFromFile("./Asset/Images/Category/Delete.png");
	}

	TextureManager::AddType TextureManager::Add;
	TextureManager::ViewType TextureManager::View;
	TextureManager::CategoryType TextureManager::Category;
	TextureManager::BudgetType TextureManager::Budget;
}