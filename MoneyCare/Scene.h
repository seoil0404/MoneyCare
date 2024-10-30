#pragma once
#include <memory>
#include "Extentions.h"

class MainUI
{
public:
	MainUI();
private:
	std::shared_ptr<sf::RectangleShapeEx> backGround;

	std::shared_ptr<sf::ButtonShape> addButton;
	std::shared_ptr<sf::TextEx> addButtonText;

	std::shared_ptr<sf::ButtonShape> viewButton;
	std::shared_ptr<sf::TextEx> viewButtonText;

	std::shared_ptr<sf::ButtonShape> categoryButton;
	std::shared_ptr<sf::TextEx> categoryButtonText;

	std::shared_ptr<sf::ButtonShape> budgetButton;
	std::shared_ptr<sf::TextEx> budgetButtonText;
};

class SceneManager
{
public:
	enum class SceneType
	{
		Add,
		View,
		Category,
		Budget
	};

	static void MoveScene();
};