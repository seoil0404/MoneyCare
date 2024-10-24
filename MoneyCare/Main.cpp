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
#include "Coroutine.h"
#include "Category.h"
#include "DataManager.h"
#include "Json.h"

void start();
void test1();

int main()
{
	start();
	while (true)
	{
		Coroutine::updateFunctions();
	}
}

void start()
{
	DataManager::AddLayer();

	CategoryManager::AddCategory(Category("Test1"));
	CategoryManager::AddCategory(Category("Test2"));
	CategoryManager::AddCategory(Category("Test3"));
	
	Layer& layer = DataManager::getRecentLayer();
	
	layer.AddItem(Item(100, "test1", CategoryManager::getAllCategoryData()[0]));
	layer.AddItem(Item(150, "test2", CategoryManager::getAllCategoryData()[2]));
	layer.AddItem(Item(100, "test3", CategoryManager::getAllCategoryData()[1]));

	JsonManager::SaveData(DataManager::getAllLayer(), CategoryManager::getAllCategoryData());
}

void test1()
{
	CategoryManager::AddCategory(Category("Category1"));
	CategoryManager::AddCategory(Category("Category2"));
	CategoryManager::AddCategory(Category("Category3"));
	CategoryManager::AddCategory(Category("Category4"));
	CategoryManager::AddCategory(Category("Category5"));
	CategoryManager::AddCategory(Category("Category6"));
	CategoryManager::DeleteCategory(Category("Category3"));
	for (Category index : CategoryManager::getAllCategoryDataRef())
	{
		std::cout << index.getCategoryName() << " ";
	}
}