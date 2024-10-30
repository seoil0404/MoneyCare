#pragma once
#include <memory>
#include "Extentions.h"

enum class SceneType
{
	Add,
	View,
	Category,
	Budget
};

class MainUI
{
public:
	MainUI();
private:
	SceneType type;
	std::shared_ptr<sf::RectangleShapeEx> backGround;

	std::shared_ptr<sf::ButtonShape> addButton;
	std::shared_ptr<sf::TextEx> addButtonText;

	std::shared_ptr<sf::ButtonShape> viewButton;
	std::shared_ptr<sf::TextEx> viewButtonText;

	std::shared_ptr<sf::ButtonShape> categoryButton;
	std::shared_ptr<sf::TextEx> categoryButtonText;

	std::shared_ptr<sf::ButtonShape> budgetButton;
	std::shared_ptr<sf::TextEx> budgetButtonText;

	void PrintAdd();
	void PrintView();
	void PrintCategory();
	void PrintBudget();

	void OnHovering(std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>);
	
	void OutHovering(std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>);

	void Click(std::shared_ptr<sf::ButtonShape>);
	void ClickOther();

	void ClickAdd();
	void ClickView();
	void ClickCategory();
	void ClickBudget();

	void DeletePreScene();
};

class SceneManager
{
public:
	

	static void MoveScene();
};