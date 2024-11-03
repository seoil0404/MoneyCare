#include "Scene.h"
#include "Loads.h"
#include "WindowManager.h"
#include "DataManager.h"

ViewScene::ViewScene()
{
	title = sf::TextEx::Create(sf::FontManager::Black, "VIEW", 80, sf::Vector2f(500, 50));
	title->setFillColor(sf::Color::Black);

	PrintScroll();
	currentView = nullptr;

	

	Translate(sf::Vector2f(-1600, 0), 100);
}

void ViewScene::ScrollTranslate(sf::Vector2f position, float speed)
{
	for (auto index : viewButton)
	{
		index->Translate(position, speed);
	}
	for (auto index : viewAmountText)
	{
		index->Translate(position, speed);
	}
	for (auto index : viewLayerLine)
	{
		index->Translate(position, speed);
	}
}

void ViewScene::setScroll()
{
	WindowManager::setUpScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::View) ScrollTranslate(sf::Vector2f(0, 100), 3);}
	);
	WindowManager::setDownScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::View) ScrollTranslate(sf::Vector2f(0, -100), 3); }
	);
}

void ViewScene::Translate(sf::Vector2f position, float speed)
{
	title->Translate(position, speed);

	if (name != nullptr) name->Translate(position, speed);
	if (amount != nullptr) amount->Translate(position, speed);
	if (category != nullptr) category->Translate(position, speed);

	if (usage != nullptr) usage->Translate(position, speed);
	if (usageGraph != nullptr) usageGraph->Translate(position, speed);

	if (inCategoryUsage != nullptr) inCategoryUsage->Translate(position, speed);
	if (inCategoryUsageGraph != nullptr) inCategoryUsageGraph->Translate(position, speed);

	if (categoryUsage != nullptr) categoryUsage->Translate(position, speed);
	if (categoryUsageGraph != nullptr) categoryUsageGraph->Translate(position, speed);

	if (budgetUsage != nullptr) budgetUsage->Translate(position, speed);
	if (budgetUsageGraph != nullptr) budgetUsageGraph->Translate(position, speed);

	ScrollTranslate(position, speed);
}

void ViewScene::PrintScroll()
{
	int tray = 0;
	for (int layerIndex = 0; layerIndex < DataManager::getAllLayerRef().size(); layerIndex++)
	{
		viewLayerLine.push_back(sf::RectangleShapeEx::Create(sf::Vector2f(337, 75), sf::Vector2f(1400, 65 + tray * 90)));
		viewLayerLine.back()->setTexture(&sf::TextureManager::View.LayerLine);

		tray++;
		for (int itemIndex = 0; itemIndex < DataManager::getAllLayerRef()[layerIndex].getItemDataRef().size() ; itemIndex++)
		{
			std::shared_ptr<sf::ButtonShape> tempButton = sf::ButtonShape::Create(sf::Vector2f(337, 75), sf::Vector2f(1400, 65 + tray * 90));
			std::shared_ptr<sf::TextEx> tempText = sf::TextEx::Create(
				sf::FontManager::Light,
				std::to_string( DataManager::getAllLayerRef()[layerIndex].getItemDataRef()[itemIndex].getAmount()),
				40,
				sf::Vector2f(1400, 55 + tray * 90)
			);
			tempText->setFillColor(sf::Color::Black);
			
			if (DataManager::getAllLayerRef()[layerIndex].getItemDataRef()[itemIndex].getAmount() >= 0)
			{
				tempButton->setTexture(&sf::TextureManager::View.PositiveItem);
			}
			else
			{
				tempButton->setTexture(&sf::TextureManager::View.NegativeItem);
			}

			viewButton.push_back(tempButton);
			viewAmountText.push_back(tempText);
			viewButton.back()->setClickEvent(
				[&,layerIndex, itemIndex, tray]() {
					if (currentView != nullptr) UnColorView(*currentView);
					std::string amount = viewAmountText[tray - (layerIndex + 1)]->getString();
					ColorView(viewButton[tray-(layerIndex+1)], std::stoi(amount));
					currentView = &viewButton[tray - (layerIndex + 1)];
					PrintInformation(
						DataManager::getAllLayerRef()[layerIndex].getItemDataRef()[itemIndex],
						DataManager::getAllLayerRef()[layerIndex]
					);
				}
			);

			tray++;
		}
	}
}

void ViewScene::PrintInformation(Item item, Layer& layer)
{
	name = sf::TextEx::Create(sf::FontManager::Light, "Name | ", 40, sf::Vector2f(460, 175));
	name->setFillColor(sf::Color::Black);
	name->setString(name->getString() + item.getUsageName());

	amount = sf::TextEx::Create(sf::FontManager::Light, "Amount | ", 40, sf::Vector2f(480, 235));
	amount->setFillColor(sf::Color::Black);
	amount->setString(amount->getString() + std::to_string(item.getAmount()));

	category = sf::TextEx::Create(sf::FontManager::Light, "Category | ", 40, sf::Vector2f(485, 295));
	category->setFillColor(sf::Color::Black);
	category->setString(category->getString() + item.getCategory().getCategoryName());

	float posAllAmount = layer.getTotalAmount().first;
	float negAllAmount = layer.getTotalAmount().second;

	float posCategoryAmount = layer.getTotalAmountInCategory(item.getCategory()).first;
	float negCategoryAmount = layer.getTotalAmountInCategory(item.getCategory()).second;

	float budgetAmount = layer.getBudgetValue(item.getCategory());

	float _usage = 0;
	float _inCategoryUsage = 0;
	float _categoryUsage = 0;
	float _budgetUsage = 0;

	if (item.getAmount() >= 0)
	{
		_usage = item.getAmount() / posAllAmount * 100;
		_inCategoryUsage = item.getAmount() / posCategoryAmount * 100;
		_categoryUsage = posCategoryAmount / posAllAmount * 100;
	}
	else
	{
		_usage = item.getAmount() / negAllAmount * 100;
		_inCategoryUsage = item.getAmount() / negCategoryAmount * 100;
		_categoryUsage = negCategoryAmount / negAllAmount * 100;
		_budgetUsage = negCategoryAmount / (-budgetAmount) * 100;
		if (budgetAmount == 0) _budgetUsage = 100;
	}

	usage = sf::TextEx::Create(sf::FontManager::Light, "", 30, sf::Vector2f(405, 395));
	usage->setFillColor(sf::Color::Black);
	usage->setString("Usage | " + std::to_string(_usage) + "%");

	inCategoryUsage = sf::TextEx::Create(sf::FontManager::Light, "", 30, sf::Vector2f(405, 495));
	inCategoryUsage->setFillColor(sf::Color::Black);
	inCategoryUsage->setString("In Category Usage | " + std::to_string(_inCategoryUsage) + "%");

	categoryUsage = sf::TextEx::Create(sf::FontManager::Light, "", 30, sf::Vector2f(405, 595));
	categoryUsage->setFillColor(sf::Color::Black);
	categoryUsage->setString("Category Usage | " + std::to_string(_categoryUsage) + "%");

	usageGraph = sf::RectangleShapeEx::Create(sf::Vector2f(7, 45), sf::Vector2f(400, 465));
	usageGraph->setOrigin(sf::Vector2f(0, 22.5f));
	usageGraph->Resize(sf::Vector2f(_usage, 1), 3);

	inCategoryUsageGraph = sf::RectangleShapeEx::Create(sf::Vector2f(7, 45), sf::Vector2f(400, 565));
	inCategoryUsageGraph->setOrigin(sf::Vector2f(0, 22.5f));
	inCategoryUsageGraph->Resize(sf::Vector2f(_inCategoryUsage, 1), 3);

	categoryUsageGraph = sf::RectangleShapeEx::Create(sf::Vector2f(7, 45), sf::Vector2f(400, 665));
	categoryUsageGraph->setOrigin(sf::Vector2f(0, 22.5f));
	categoryUsageGraph->Resize(sf::Vector2f(_categoryUsage, 1), 3);

	sf::Color red = sf::Color(255, 89, 89);
	sf::Color green = sf::Color(78, 167, 46);

	if (item.getAmount() < 0)
	{
		usageGraph->setFillColor(red);
		inCategoryUsageGraph->setFillColor(red);
		categoryUsageGraph->setFillColor(red);

		budgetUsage = sf::TextEx::Create(sf::FontManager::Light, "", 30, sf::Vector2f(405, 695));
		budgetUsage->setFillColor(sf::Color::Black);
		budgetUsage->setString("Budget Usage | " + std::to_string(_budgetUsage) + "%");

		budgetUsageGraph = sf::RectangleShapeEx::Create(sf::Vector2f(7, 45), sf::Vector2f(400, 765));
		budgetUsageGraph->setOrigin(sf::Vector2f(0, 22.5f));
		budgetUsageGraph->Resize(sf::Vector2f(_budgetUsage, 1), 3);
		budgetUsageGraph->setFillColor(red);
	}
	else
	{
		usageGraph->setFillColor(green);
		inCategoryUsageGraph->setFillColor(green);
		categoryUsageGraph->setFillColor(green);

		budgetUsage.reset();
		budgetUsageGraph.reset();
	}
}

void ViewScene::ColorView(std::shared_ptr<sf::ButtonShape> button, int amount)
{
	if (amount >= 0)
	{
		button->setTexture(&sf::TextureManager::View.PositiveSelectedItem);
	}
	else
	{
		button->setTexture(&sf::TextureManager::View.NegativeSelectedItem);
	}
}

void ViewScene::UnColorView(std::shared_ptr<sf::ButtonShape> button)
{
	if (button->getTexture() == &sf::TextureManager::View.PositiveSelectedItem)
	{
		button->setTexture(&sf::TextureManager::View.PositiveItem);
	}
	else
	{
		button->setTexture(&sf::TextureManager::View.NegativeItem);
	}
}

void ViewScene::Initialize()
{
	name = nullptr;
	amount = nullptr;
	category = nullptr;

	usage = nullptr;
	usageGraph = nullptr;

	inCategoryUsage = nullptr;
	inCategoryUsageGraph = nullptr;

	categoryUsage = nullptr;
	categoryUsageGraph = nullptr;

	budgetUsage = nullptr;
	budgetUsageGraph = nullptr;
}