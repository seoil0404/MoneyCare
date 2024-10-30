#include "Scene.h"
#include "Fonts.h"

MainUI::MainUI()
{
	backGround = sf::RectangleShapeEx::Create(sf::Vector2f(350, 900), sf::Vector2f(175, 450));
	backGround->setFillColor(sf::Color(50, 124, 222));
	
	addButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 300));
	addButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"���� ��ȸ", 25, sf::Vector2f(90, 297));
	addButtonText->setFillColor(sf::Color::Black);

	viewButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 450));
	viewButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"���� �Է�", 25, sf::Vector2f(90, 447));
	viewButtonText->setFillColor(sf::Color::Black);

	categoryButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 600));
	categoryButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"ī�װ� �߰�", 25, sf::Vector2f(113, 597));
	categoryButtonText->setFillColor(sf::Color::Black);

	budgetButton = sf::ButtonShape::Create(sf::Vector2f(195, 60), sf::Vector2f(120, 750));
	budgetButtonText = sf::TextEx::Create(sf::FontManager::Regular, L"���� ����", 25, sf::Vector2f(90, 747));
	budgetButtonText->setFillColor(sf::Color::Black);
}