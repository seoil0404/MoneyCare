#pragma once
#include <memory>
#include "Extentions.h"
#include "DataManager.h"

enum class SceneType
{
	Add,
	View,
	Category,
	Budget,
	None
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
	~AddScene() {};

	void Translate(sf::Vector2f, float);
	
	void ScrollTranslate(sf::Vector2f, float);
	
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
	ViewScene();
	~ViewScene() {};

	void Translate(sf::Vector2f, float);

	void ScrollTranslate(sf::Vector2f, float);

	void setScroll();

private:
	void PrintScroll();
	void PrintInformation(Item, Layer&);

	void Initialize();

	std::shared_ptr<sf::TextEx> title;
	
	std::shared_ptr<sf::TextEx> name;
	std::shared_ptr<sf::TextEx> amount;
	std::shared_ptr<sf::TextEx> category;

	std::shared_ptr<sf::TextEx> usage;
	std::shared_ptr<sf::RectangleShapeEx> usageGraph;

	std::shared_ptr<sf::TextEx> inCategoryUsage;
	std::shared_ptr<sf::RectangleShapeEx> inCategoryUsageGraph;
	
	std::shared_ptr<sf::TextEx> categoryUsage;
	std::shared_ptr<sf::RectangleShapeEx> categoryUsageGraph;

	std::shared_ptr<sf::TextEx> budgetUsage;
	std::shared_ptr<sf::RectangleShapeEx> budgetUsageGraph;

	std::vector<std::shared_ptr<sf::ButtonShape>> viewButton;
	std::vector<std::shared_ptr<sf::TextEx>> viewAmountText;

	std::shared_ptr<sf::ButtonShape>* currentView;

	void ColorView(std::shared_ptr<sf::ButtonShape>, int);
	void UnColorView(std::shared_ptr<sf::ButtonShape>);

	std::vector<std::shared_ptr<sf::RectangleShapeEx>> viewLayerLine;
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
	BudgetScene();

	void Translate(sf::Vector2f, float);

	void ScrollTranslate(sf::Vector2f, float);

	void setScroll();

private:
	void PrintScroll();

	std::shared_ptr<sf::TextEx> title;

	std::shared_ptr<sf::TextEx> amountText;
	std::shared_ptr<sf::ButtonShape> amountInputButton;
	std::shared_ptr<sf::TextEx> amountInputField;

	std::shared_ptr<sf::TextEx> categoryText;
	std::shared_ptr<sf::ButtonShape> categoryInputButton;
	std::shared_ptr<sf::TextEx> categoryInputField;

	std::shared_ptr<sf::ButtonShape> addButton;

	std::vector<std::vector<std::pair<std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>>>> view;
	std::vector<std::shared_ptr<sf::RectangleShapeEx>> viewLayerLine;

	void Initialize();
	void PrintField(Layer&);
	
	std::vector<std::pair<std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>>>* currentView;

	void ColorView(std::vector<std::pair<std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>>>&);
	void UnColorView(std::vector<std::pair<std::shared_ptr<sf::ButtonShape>, std::shared_ptr<sf::TextEx>>>&);
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