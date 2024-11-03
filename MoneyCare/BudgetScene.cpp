#include "Scene.h"
#include "Loads.h"
#include "DataManager.h"
#include "WindowManager.h"
#include "DebugLog.h"

BudgetScene::BudgetScene()
{
	title = sf::TextEx::Create(sf::FontManager::Black, "BUDGET", 80, sf::Vector2f(550, 50));
	title->setFillColor(sf::Color::Black);
	
	PrintScroll();

	Translate(sf::Vector2f(-1600, 0), 100);
}

void BudgetScene::Translate(sf::Vector2f position, float speed)
{
	title->Translate(position, speed);

	if (amountText != nullptr) amountText->Translate(position, speed);
	if (amountInputButton != nullptr) amountInputButton->Translate(position, speed);
	if (amountInputField != nullptr) amountInputField->Translate(position, speed);

	if (categoryText != nullptr) categoryText->Translate(position, speed);
	if (categoryInputButton != nullptr) categoryInputButton->Translate(position, speed);
	if (categoryInputField != nullptr) categoryInputField->Translate(position, speed);

	if (addButton != nullptr) addButton->Translate(position, speed);

	ScrollTranslate(position, speed);
}

void BudgetScene::ScrollTranslate(sf::Vector2f position, float speed)
{
	for (auto index : view)
	{
		for (auto pair : index)
		{
			pair.first->Translate(position, speed);
			pair.second->Translate(position, speed);
		}
	}

	for (auto index : viewLayerLine)
	{
		index->Translate(position, speed);
	}
}

void BudgetScene::setScroll()
{
	WindowManager::setUpScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::Budget) ScrollTranslate(sf::Vector2f(0, 100), 3);}
	);
	WindowManager::setDownScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::Budget) ScrollTranslate(sf::Vector2f(0, -100), 3); }
	);
}

void BudgetScene::PrintScroll()
{
	int tray = 0;
	int layerNum = 0;

	for (auto layer : DataManager::getAllLayerRef())
	{
		viewLayerLine.push_back(sf::RectangleShapeEx::Create(sf::Vector2f(337, 75), sf::Vector2f(1400, 65 + tray * 90)));
		viewLayerLine.back()->setTexture(&sf::TextureManager::Budget.LayerLine);
		
		tray++;
		
		view.push_back(std::vector < std::pair<std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>>>());

		for (auto item : layer.getItemData())
		{
			std::shared_ptr<sf::ButtonShape> tempButton = sf::ButtonShape::Create(
				sf::Vector2f(337, 75), 
				sf::Vector2f(1400, 65 + tray * 90)
			);

			std::shared_ptr<sf::TextEx> tempText = sf::TextEx::Create(
				sf::FontManager::Light,
				std::to_string(item.getAmount()),
				40,
				sf::Vector2f(1400, 55 + tray * 90)
			);

			tempText->setFillColor(sf::Color::Black);

			if (item.getAmount() >= 0)
			{
				tempButton->setTexture(&sf::TextureManager::Budget.PositiveItem);
			}
			else
			{
				tempButton->setTexture(&sf::TextureManager::Budget.NegativeItem);
			}

			tempButton->setClickEvent(
				[&, layerNum]() {
					Initialize();
					PrintField(DataManager::getAllLayerRef()[layerNum]);
				}
			);

			view.back().push_back(
				std::pair<std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>>(tempButton, tempText)
			);
			tray++;
		}
		layerNum++;
	}
}

void BudgetScene::Initialize()
{
	amountText.reset();
	amountInputButton.reset();
	amountInputField.reset();

	categoryText.reset();
	categoryInputButton.reset();
	categoryInputField.reset();

	addButton.reset();
}

void BudgetScene::PrintField(Layer& layer)
{
	categoryText = sf::TextEx::Create(sf::FontManager::Light, "Category", 50, sf::Vector2f(500, 275));
	categoryText->setFillColor(sf::Color::Black);
	categoryInputButton = sf::ButtonShape::Create(sf::Vector2f(600, 60), sf::Vector2f(690, 355));
	categoryInputButton->setTexture(&sf::TextureManager::Add.Input);
	categoryInputField = sf::TextEx::Create(sf::FontManager::Regular, "", 40, sf::Vector2f(410, 330));
	categoryInputField->setFillColor(sf::Color::Black);
	categoryInputField->setString(layer.getBudgetData().front().getCategory().getCategoryName());

	amountText = sf::TextEx::Create(sf::FontManager::Light, "Amount", 50, sf::Vector2f(495, 425));
	amountText->setFillColor(sf::Color::Black);
	amountInputButton = sf::ButtonShape::Create(sf::Vector2f(600, 60), sf::Vector2f(690, 505));
	amountInputButton->setTexture(&sf::TextureManager::Add.Input);
	amountInputField = sf::TextEx::Create(sf::FontManager::Regular, "", 40, sf::Vector2f(410, 480));
	amountInputField->setString(amountInputField->getString() + std::to_string(layer.getBudgetData().front().getAmount()));
	amountInputField->setFillColor(sf::Color::Black);

	amountInputButton->setClickEvent(
		[&]() { WindowManager::setInputDigitField(amountInputField); }
	);
	
	amountInputButton->setExitClickEvent(
		[&]() { WindowManager::setInputDigitField(nullptr); }
	);

	categoryInputButton->setClickEvent(
		[&]() {
			Budget budget = layer.getNextBudget(Category(categoryInputField->getString()));
			categoryInputField->setString(budget.getCategory().getCategoryName());
			amountInputField->setString(std::to_string(budget.getAmount()));
		}
	);

	addButton = sf::ButtonShape::Create(sf::Vector2f(125, 50), sf::Vector2f(920, 600));
	addButton->setTexture(&sf::TextureManager::Add.AddItem);

	addButton->setClickEvent(
		[&]() {
			if (amountInputField->getString().getSize() > 0 && categoryInputField->getString().getSize() > 0)
			{
				std::string tempAmount = amountInputField->getString();
				layer.setBudgetValue(Category(categoryInputField->getString()), std::stoi(tempAmount));
				SceneManager::UpdateScene();
			}
		}
	);
}