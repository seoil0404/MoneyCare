/*
 * Program Name: MoneyCare
 * Author: Bae-Seoil
 * Created: 2024-11-04
 * Description: A program for recording and managing usage history.
 * You can use, copy, modify, and distribute this program freely.
 */

#include <functional>
#include <queue>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Extentions.h"
#include "Coroutine.h"
#include "Category.h"
#include "DataManager.h"
#include "Json.h"
#include "Global.h"
#include "DebugLog.h"
#include "WindowManager.h"
#include "Loads.h"
#include "Scene.h"

void Start();

void TestDataSettings();

int main()
{
	JsonManager::LoadData(DataManager::getAllLayerRef(), CategoryManager::getAllCategoryDataRef());

	Global::ClockUpdate();

	WindowManager::Initialize();
	sf::FontManager::Initialize();
	sf::TextureManager::Initialize();
	
	WindowManager::EventUpdate();
	
	Start();
	
	WindowManager::DisplayWindow();
	WindowManager::ClearWindow();
	
	while (true)
	{
		Coroutine::updateFunctions();
	}
}

void Start()
{
	SceneManager::Initialize();

	static MainUI mainUI;
}

void TestDataSettings()
{
	CategoryManager::AddCategory(Category("Category1"));
	CategoryManager::AddCategory(Category("Category2"));
	CategoryManager::AddCategory(Category("Category3"));

	DataManager::AddLayer();
	
	DataManager::getRecentLayer().AddItem(Item(100, "Item1", CategoryManager::getAllCategoryDataRef()[2]));
	DataManager::getRecentLayer().AddItem(Item(100, "Item2", CategoryManager::getAllCategoryDataRef()[1]));
	DataManager::getRecentLayer().AddItem(Item(100, "Item3", CategoryManager::getAllCategoryDataRef()[0]));

	DataManager::getRecentLayer().setBudgetValue(Category("Category1"), 1000);
	DataManager::getRecentLayer().setBudgetValue(Category("Category1"), 3000);
}