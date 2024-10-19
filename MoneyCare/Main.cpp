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

void start();

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
	CategoryManager::AddCategory(Category("Category1"));
	CategoryManager::AddCategory(Category("Category2"));
	CategoryManager::AddCategory(Category("Category3"));
	CategoryManager::AddCategory(Category("Category4"));
	CategoryManager::AddCategory(Category("Category5"));
	CategoryManager::AddCategory(Category("Category6"));
	//CategoryManager::DeleteCategory("Category3");
	CategoryManager::DeleteCategory(CategoryManager::getAllCategoryData()[4]);
	for (Category index : CategoryManager::getAllCategoryData())
	{
		std::cout << index.getCategoryName() << " ";
	}
}