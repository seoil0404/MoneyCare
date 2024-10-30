#include "Scene.h"
#include "Fonts.h"
#include "DebugLog.h"

MainUI::MainUI()
{
	PrintAdd();
	PrintView();
	PrintCategory();
	PrintBudget();

	Click(addButton);
	ClickAdd();
	type = SceneType::Add;
}

void MainUI::OnHovering(std::shared_ptr<sf::ButtonShape> object, std::shared_ptr<sf::TextEx> text)
{
	object->Resize(sf::Vector2f(1.5f, 1), 4);
	object->Translate(sf::Vector2f(50, 0), 4);
	text->Translate(sf::Vector2f(75, 0), 4);
}

void MainUI::Click(std::shared_ptr<sf::ButtonShape> object)
{
	ClickOther();
	DeletePreScene();
	object->setFillColor(sf::Color(159, 159, 159));
}

void MainUI::OutHovering(std::shared_ptr<sf::ButtonShape> object, std::shared_ptr<sf::TextEx> text)
{
	object->Resize(sf::Vector2f(1, 1), 4);
	object->Translate(sf::Vector2f(-50, 0), 4);
	text->Translate(sf::Vector2f(-75, 0), 4);
}

void MainUI::ClickOther()
{
	addButton->setFillColor(sf::Color::White);
	viewButton->setFillColor(sf::Color::White);
	categoryButton->setFillColor(sf::Color::White);
	budgetButton->setFillColor(sf::Color::White);
}

void MainUI::ClickAdd()
{

}

void MainUI::ClickView()
{

}

void MainUI::ClickCategory()
{

}

void MainUI::ClickBudget()
{

}

void MainUI::DeletePreScene()
{

}

void MainUI::PrintAdd()
{
	backGround = sf::RectangleShapeEx::Create(sf::Vector2f(350, 900), sf::Vector2f(175, 450));
	backGround->setFillColor(sf::Color(50, 124, 222));

	addButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 300));
	addButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"내역 조회", 25, sf::Vector2f(90, 297));
	addButtonText->setFillColor(sf::Color::Black);
	addButton->setEnterEvent(
		[&]() { OnHovering(addButton, addButtonText);}
	);
	addButton->setClickEvent(
		[&]() { Click(addButton); }
	);
	addButton->setExitEvent(
		[&]() { OutHovering(addButton, addButtonText);}
	);
}

void MainUI::PrintView()
{
	viewButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 450));
	viewButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"내역 입력", 25, sf::Vector2f(90, 447));
	viewButtonText->setFillColor(sf::Color::Black);
	viewButton->setEnterEvent(
		[&]() { OnHovering(viewButton, viewButtonText);}
	);
	viewButton->setClickEvent(
		[&]() { Click(viewButton); }
	);
	viewButton->setExitEvent(
		[&]() { OutHovering(viewButton, viewButtonText);}
	);
}

void MainUI::PrintCategory()
{
	categoryButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 600));
	categoryButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"카테고리 추가", 25, sf::Vector2f(113, 597));
	categoryButtonText->setFillColor(sf::Color::Black);
	categoryButton->setEnterEvent(
		[&]() { OnHovering(categoryButton, categoryButtonText);}
	);
	categoryButton->setClickEvent(
		[&]() { Click(categoryButton); }
	);
	categoryButton->setExitEvent(
		[&]() { OutHovering(categoryButton, categoryButtonText);}
	);
}

void MainUI::PrintBudget()
{
	budgetButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 750));
	budgetButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"예산 편집", 25, sf::Vector2f(90, 747));
	budgetButtonText->setFillColor(sf::Color::Black);
	budgetButton->setEnterEvent(
		[&]() { OnHovering(budgetButton, budgetButtonText);}
	);
	budgetButton->setClickEvent(
		[&]() { Click(budgetButton); }
	);
	budgetButton->setExitEvent(
		[&]() { OutHovering(budgetButton, budgetButtonText);}
	);
}