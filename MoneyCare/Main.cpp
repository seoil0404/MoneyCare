/*
 * Program Name: MoneyCare
 * Author: Bae-Seoil
 * Created: 2024-11-04
 * Description: A program for recording and managing usage history.
 * You can use, copy, modify, and distribute this program freely.
 */

#include "Coroutine.h"
#include "Category.h"
#include "DataManager.h"
#include "Json.h"
#include "Global.h"
#include "WindowManager.h"
#include "Loads.h"
#include "Scene.h"

void Start();

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
	SceneManager::MoveScene(SceneType::Add);
}