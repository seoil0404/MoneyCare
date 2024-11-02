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

// MainUI -------------------------------------------------------------------------------------

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

	void Click(std::shared_ptr<sf::ButtonShape>, SceneType);
	void ClickOther();
};

// Scene[abstract] -------------------------------------------------------------------------------------

class Scene
{
public:
	virtual void Translate(sf::Vector2f, float) = 0;
	virtual ~Scene() = 0;
};

// AddScene -------------------------------------------------------------------------------------

class AddScene : public Scene
{
public:
	AddScene();
	void Translate(sf::Vector2f, float);
	void ScrollTranslate(sf::Vector2f, float);
	~AddScene() {};
	void setScroll();
private:
	void PrintScroll();

	std::shared_ptr<sf::TextEx> title;

	std::shared_ptr<sf::ButtonShape> addStartButton;

	std::shared_ptr<sf::ButtonShape> addLayerButton;

	std::shared_ptr<sf::TextEx> amountText;
	std::shared_ptr<sf::ButtonShape> amountInputButton;
	std::shared_ptr<sf::TextEx> amountInputField;

	std::shared_ptr<sf::TextEx> nameText;
	std::shared_ptr<sf::ButtonShape> nameInputButton;
	std::shared_ptr<sf::TextEx> nameInputField;

	std::shared_ptr<sf::TextEx> categoryText;
	std::shared_ptr<sf::ButtonShape> categoryInputButton;
	std::shared_ptr<sf::TextEx> categoryInputField;

	std::shared_ptr<sf::ButtonShape> addItemButton;

	void PrintAmount();
	void PrintName();
	void PrintCategory();
	void PrintAddItem();

	void Initialize();

	std::vector<std::shared_ptr<sf::ButtonShape>> viewButton;
	std::vector<std::shared_ptr<sf::TextEx>> viewAmountText;
	std::vector<std::shared_ptr<sf::RectangleShapeEx>> viewLayerLine;

	std::shared_ptr<sf::ButtonShape> deleteButton;
};

// ViewScene -------------------------------------------------------------------------------------

class ViewScene : public Scene
{
public:
	void Translate(sf::Vector2f, float);
	~ViewScene() {};
};

// CategoryScene -------------------------------------------------------------------------------------

class CategoryScene : public Scene
{
public:
	CategoryScene();
	~CategoryScene() {};
	void Translate(sf::Vector2f, float);
	void setScroll();
private:
	std::shared_ptr<sf::TextEx> title;

	std::shared_ptr<sf::TextEx> inputButtonText;
	std::shared_ptr<sf::ButtonShape> inputButton;
	std::shared_ptr<sf::TextEx> inputField;

	std::shared_ptr<sf::ButtonShape> addButton;

	std::vector<std::shared_ptr<sf::ButtonShape>> categoryButton;
	std::vector<std::shared_ptr<sf::TextEx>> categoryText;

	std::shared_ptr<sf::ButtonShape> deleteButton;
};

// BudgetScene -------------------------------------------------------------------------------------

class BudgetScene : public Scene
{
public:
	void Translate(sf::Vector2f, float);
};

// SceneManager -------------------------------------------------------------------------------------

class SceneManager
{
public:
	static void Initialize();
	static void UpdateScene();
	static void MoveScene(SceneType);
	static SceneType getCurrentScene() { return scene; };

private:
	static AddScene* addScene;
	static ViewScene* viewScene;
	static CategoryScene* categoryScene;
	static BudgetScene* budgetScene;

	static SceneType scene;

	static void ClearScene(SceneType);
	static void IncludeScene(SceneType);
};