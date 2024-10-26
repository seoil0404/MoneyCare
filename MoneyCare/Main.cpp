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

void Start();

int main()
{
	Time::ClockUpdate();

	WindowManager::EventUpdate();
	WindowManager::ClearWindow();
	
	Start();
	
	WindowManager::DisplayWindow();
	
	while (true)
	{
		Coroutine::updateFunctions();
	}
}

void Start()
{
	sf::RectangleShapeEx* a = sf::RectangleShapeEx::Create(sf::Vector2f(100, 100));
	a->setPosition(sf::Vector2f(750, 450));
}