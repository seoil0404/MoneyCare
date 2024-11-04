#include "Scene.h"
#include "Loads.h"
#include "DataManager.h"
#include "DebugLog.h"
#include "WindowManager.h"
#include "string"
#include "Category.h"
#include "Coroutine.h"

AddScene::AddScene()
{
	if (DataManager::IsEmpty())
	{
		DataManager::AddLayer();
	}
	
	title = sf::TextEx::Create(sf::FontManager::Black, "ADD", 80, sf::Vector2f(480, 50));
	title->setFillColor(sf::Color::Black);

	addStartButton = sf::ButtonShape::Create(sf::Vector2f(50, 50), sf::Vector2f(420, 200));
	addStartButton->setTexture(&sf::TextureManager::Add.Add);
	if (CategoryManager::CategoryDataSize() == 0)
	{
		disableText = sf::TextEx::Create(sf::FontManager::Light, "Add Category First!", 20, sf::Vector2f(483, 120));
		disableText->setFillColor(sf::Color::Red);
	}

	addLayerButton = sf::ButtonShape::Create(sf::Vector2f(156, 48), sf::Vector2f(550, 200));
	addLayerButton->setTexture(&sf::TextureManager::Add.AddLayer);

	addStartButton->setClickEvent(
		[&]() { 
			if (CategoryManager::CategoryDataSize() != 0)
			{
				Initialize();
				PrintAmount();
			}
		}
	);

	addLayerButton->setClickEvent(
		[&]() {
			if (DataManager::getRecentLayer().getItemData().size() > 0)
			{
				DataManager::AddLayer();
				SceneManager::UpdateScene();
			}
		}
	);

	PrintScroll();

	Translate(sf::Vector2f(-1600, 0), 100);
}

void AddScene::ScrollTranslate(sf::Vector2f position, float speed)
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
	if (deleteButton != nullptr) deleteButton->Translate(position, speed);
}

void AddScene::Translate(sf::Vector2f position, float speed)
{
	title->Translate(position, speed);
	addStartButton->Translate(position, speed);
	addLayerButton->Translate(position, speed);

	if (disableText != nullptr) disableText->Translate(position, speed);

	if (amountText != nullptr) amountText->Translate(position, speed);
	if (amountInputButton != nullptr) amountInputButton->Translate(position, speed);
	if (amountInputField != nullptr) amountInputField->Translate(position, speed);

	if (nameText != nullptr) nameText->Translate(position, speed);
	if (nameInputButton != nullptr) nameInputButton->Translate(position, speed);
	if (nameInputField != nullptr) nameInputField->Translate(position, speed);

	if (categoryText != nullptr) categoryText->Translate(position, speed);
	if (categoryInputButton != nullptr) categoryInputButton->Translate(position, speed);
	if (categoryInputField != nullptr) categoryInputField->Translate(position, speed);

	if (addItemButton != nullptr) addItemButton->Translate(position, speed);

	ScrollTranslate(position, speed);
}

void AddScene::PrintScroll()
{
	int tray = 0;
	int index = 0;
	int layerIndex = 0;
	for (Layer layer : DataManager::getAllLayer())
	{
		viewLayerLine.push_back(sf::RectangleShapeEx::Create(sf::Vector2f(337, 75), sf::Vector2f(1400, 65 + tray * 90)));
		viewLayerLine.back()->setTexture(&sf::TextureManager::Add.LayerLine);
		tray++;

		int itemIndex = 0;
		for (Item item : layer.getItemData())
		{
			viewButton.push_back(
				sf::ButtonShape::Create(
					sf::Vector2f(337, 75),
					sf::Vector2f(1400, 65 + tray * 90)
				)
			);

			viewButton.back()->setClickEvent(
				[&, layerIndex, itemIndex, index, tray, item]() {

					ColorView(viewButton[tray - (layerIndex + 1)], item.getAmount());
					if (currentView != nullptr) UnColorView(*currentView);
					currentView = &viewButton[tray - (layerIndex + 1)];

					deleteButton = sf::ButtonShape::Create(sf::Vector2f(1, 1), viewButton[index]->getPosition() + sf::Vector2f(-260, 0));
					deleteButton->Resize(sf::Vector2f(150, 60), 10);
					deleteButton->setTexture(&sf::TextureManager::Add.Delete);

					deleteButton->setClickEvent([&]() {
							DataManager::getAllLayerRef()[layerIndex].DeleteItem(
								DataManager::getAllLayerRef()[layerIndex].getItemDataRef().begin() + itemIndex
							);
							SceneManager::UpdateScene();
							Coroutine::AddCoroutine([&]() {deleteButton.reset();});
						}
					);
					

					PrintAmount();
					PrintName();
					PrintCategory();
					PrintAddItem();
					WindowManager::setInputDigitField(nullptr);
					WindowManager::setInputField(nullptr);

					amountInputField->setString(
						std::to_string(DataManager::getAllLayerRef()[layerIndex].getItemData()[itemIndex].getAmount())
					);

					nameInputField->setString(
						DataManager::getAllLayerRef()[layerIndex].getItemData()[itemIndex].getUsageName()
					);

					categoryInputField->setString(
						DataManager::getAllLayerRef()[layerIndex].getItemData()[itemIndex].getCategory().getCategoryName()
					);
					

					addItemButton->setClickEvent(
						[&]() {
							if (amountInputField->getString().getSize() > 0 && nameInputField->getString().getSize() > 0 && amountInputField->getString().getSize() > 0)
							{
								std::string amount = amountInputField->getString();
								std::string name = nameInputField->getString();
								std::string category = categoryInputField->getString();
								DataManager::getAllLayerRef()[layerIndex].getItemDataRef()[itemIndex] = Item(
									std::stoi(amount),
									name,
									Category(category)
								);
								SceneManager::UpdateScene();
							}
						}
					);
				}
			);

			viewAmountText.push_back(
				sf::TextEx::Create(
					sf::FontManager::Light,
					std::to_string(item.getAmount()),
					40, 
					sf::Vector2f(1400, 55 + tray * 90)
				)
			);

			viewAmountText.back()->setFillColor(sf::Color::Black);

			if (item.getAmount() >= 0)
			{
				viewButton.back()->setTexture(&sf::TextureManager::Add.PositiveItem);
			}
			else
			{
				viewButton.back()->setTexture(&sf::TextureManager::Add.NegativeItem);
			}

			index++;
			itemIndex++;
			tray++;
		}
		layerIndex++;
	}
}

void AddScene::setScroll()
{
	WindowManager::setUpScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::Add) ScrollTranslate(sf::Vector2f(0, 100), 3);}
	);
	WindowManager::setDownScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::Add) ScrollTranslate(sf::Vector2f(0, -100), 3); }
	);
}

void AddScene::PrintAmount()
{
	amountText = sf::TextEx::Create(sf::FontManager::Light, "Amount", 50, sf::Vector2f(495, 275));
	amountText->setFillColor(sf::Color::Black);
	amountInputButton = sf::ButtonShape::Create(sf::Vector2f(600, 60), sf::Vector2f(690, 355));
	amountInputButton->setTexture(&sf::TextureManager::Add.Input);
	amountInputField = sf::TextEx::Create(sf::FontManager::Regular, "0", 40, sf::Vector2f(415, 345));
	amountInputField->setFillColor(sf::Color::Black);

	amountInputButton->setClickEvent(
		[&]() {WindowManager::setInputDigitField(amountInputField);}
	);

	amountInputButton->setExitClickEvent(
		[&]() { if (amountInputField->getString().getSize() > 0 && nameText == nullptr) PrintName(); }
	);
}

void AddScene::PrintName()
{
	nameText = sf::TextEx::Create(sf::FontManager::Light, "Expense Name", 50, sf::Vector2f(565, 425));
	nameText->setFillColor(sf::Color::Black);
	nameInputButton = sf::ButtonShape::Create(sf::Vector2f(600, 60), sf::Vector2f(690, 505));
	nameInputButton->setTexture(&sf::TextureManager::Add.Input);
	nameInputField = sf::TextEx::Create(sf::FontManager::Regular, "", 40, sf::Vector2f(410, 480));
	nameInputField->setFillColor(sf::Color::Black);

	nameInputButton->setClickEvent(
		[&]() {WindowManager::setInputField(nameInputField);}
	);

	nameInputButton->setExitClickEvent(
		[&]() { if (nameInputField->getString().getSize() > 0 && categoryText == nullptr) PrintCategory(); }
	);
}

void AddScene::PrintCategory()
{
	categoryText = sf::TextEx::Create(sf::FontManager::Light, "Category", 50, sf::Vector2f(500, 575));
	categoryText->setFillColor(sf::Color::Black);
	categoryInputButton = sf::ButtonShape::Create(sf::Vector2f(600, 60), sf::Vector2f(690, 655));
	categoryInputButton->setTexture(&sf::TextureManager::Add.Input);
	categoryInputField = sf::TextEx::Create(sf::FontManager::Regular, "", 40, sf::Vector2f(410, 630));
	categoryInputField->setFillColor(sf::Color::Black);
	
	if (CategoryManager::getAllCategoryData().size() > 0) categoryInputField->setString(CategoryManager::getAllCategoryData().front().getCategoryName());
	else categoryInputField->setString("None");

	categoryInputButton->setClickEvent(
		[&]() {
			if(CategoryManager::CategoryDataSize() > 0) categoryInputField->setString(CategoryManager::getNextCategory(Category(categoryInputField->getString())).getCategoryName());
		}
	);

	PrintAddItem();
}

void AddScene::PrintAddItem()
{
	addItemButton = sf::ButtonShape::Create(sf::Vector2f(125, 50), sf::Vector2f(920, 750));
	addItemButton->setTexture(&sf::TextureManager::Add.AddItem);

	addItemButton->setClickEvent(
		[&]() { 
			if (amountInputField->getString().getSize() > 0 && nameInputField->getString().getSize() > 0 && amountInputField->getString().getSize() > 0)
			{
				std::string amount = amountInputField->getString();
				std::string name = nameInputField->getString();
				std::string category = categoryInputField->getString();
				DataManager::getRecentLayer().AddItem(Item(
						std::stoi(amount),
						name,
						Category(category)
					)
				);
				SceneManager::UpdateScene();
			}
		}
	);
}

void AddScene::Initialize()
{
	WindowManager::setInputDigitField(nullptr);
	WindowManager::setInputField(nullptr);

	amountText = nullptr;
	amountInputButton = nullptr;
	amountInputField = nullptr;

	nameText = nullptr;
	nameInputButton = nullptr;
	nameInputField = nullptr;

	categoryText = nullptr;
	categoryInputButton = nullptr;
	categoryInputField = nullptr;

	addItemButton = nullptr;

	disableText = nullptr;
}

void AddScene::ColorView(std::shared_ptr<sf::ButtonShape> button, int amount)
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

void AddScene::UnColorView(std::shared_ptr<sf::ButtonShape> button)
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