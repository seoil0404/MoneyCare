#include "Scene.h"
#include "Category.h"
#include "Loads.h"
#include "DebugLog.h"
#include "Coroutine.h"
#include "WindowManager.h"

CategoryScene::CategoryScene()
{
	title = sf::TextEx::Create(sf::FontManager::Black, "CATEGORY", 80, sf::Vector2f(610, 50));
	title->setFillColor(sf::Color::Black);

	inputButton = sf::ButtonShape::Create(sf::Vector2f(600, 60), sf::Vector2f(695, 465));
	inputButton->setTexture(&sf::TextureManager::Category.Input);
	inputButton->setClickEvent(
		[&]() { WindowManager::setInputField(inputField); }
	);
	inputButton->setExitClickEvent(
		[&]() { WindowManager::setInputField(nullptr);}
	);

	inputField = sf::TextEx::Create(sf::FontManager::Regular, "", 30, sf::Vector2f(415, 445));
	inputField->setFillColor(sf::Color::Black);
	
	addButton = sf::ButtonShape::Create(sf::Vector2f(55, 55), sf::Vector2f(1035, 465));
	addButton->setTexture(&sf::TextureManager::Category.Add);
	addButton->setClickEvent(
		[&]() { 
			if (inputField->getString().getSize() > 0)
			{
				CategoryManager::AddCategory(inputField->getString());
				inputField->setString("");
				WindowManager::setInputField(nullptr);
				SceneManager::UpdateScene();
			}
		}
	);

	inputButtonText = sf::TextEx::Create(sf::FontManager::Light, "Add", 50, sf::Vector2f(450, 380));
	inputButtonText->setFillColor(sf::Color::Black);

	for (int index = 0; index < CategoryManager::CategoryDataSize(); index++)
	{
		categoryButton.push_back(
			sf::ButtonShape::Create(
				sf::Vector2f(500, 60),
				sf::Vector2f(650, 550 + index * 75)
			)
		);
		categoryButton.back()->setTexture(&sf::TextureManager::Category.Item);

		categoryButton.back()->setClickEvent(
			[&, index]() {
				deleteButton = sf::ButtonShape::Create(sf::Vector2f(1, 1), categoryButton[index]->getPosition() + sf::Vector2f(330, 0));
				deleteButton->Resize(sf::Vector2f(150, 60), 10);
				deleteButton->setTexture(&sf::TextureManager::Category.Delete);
				deleteButton->setClickEvent([&]() { 
					CategoryManager::DeleteCategory(CategoryManager::getAllCategoryData()[index]);
					SceneManager::UpdateScene();
					Coroutine::AddCoroutine([&]() {deleteButton.reset();});
					}
				);
				deleteButton->setExitClickEvent([&]() {Coroutine::AddCoroutine([&]() {deleteButton.reset();}); });
			}
		);

		categoryText.push_back(
			sf::TextEx::Create(
				sf::FontManager::Light,
				CategoryManager::getAllCategoryData()[index].getCategoryName(),
				35,
				sf::Vector2f(650, 545 + index * 75)
			)
		);
		categoryText.back()->setFillColor(sf::Color::Black);
	}
	
	Translate(sf::Vector2f(-1600, 0), 100);
}

void CategoryScene::Translate(sf::Vector2f position, float speed)
{
	inputButton->Translate(position, speed);
	inputButtonText->Translate(position, speed);
	title->Translate(position, speed);
	inputField->Translate(position, speed);

	if (addButton != nullptr) addButton->Translate(position, speed);
	if (deleteButton != nullptr) deleteButton->Translate(position, speed);

	for (auto index : categoryButton)
	{
		index->Translate(position, speed);
	}
	for (auto index : categoryText)
	{
		index->Translate(position, speed);
	}
}

void CategoryScene::setScroll()
{
	WindowManager::setUpScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::Category) Translate(sf::Vector2f(0, 100), 3);}
	);
	WindowManager::setDownScrollEvent(
		[&]() { if (SceneManager::getCurrentScene() == SceneType::Category) Translate(sf::Vector2f(0, -100), 3); }
	);
}