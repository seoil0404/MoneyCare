#include "Category.h"

std::string Category::getCategoryName()
{
	return categoryName;
}

Category::Category(std::string name)
{
	categoryName = name;
}

Category::Category(Category& category)
{
	categoryName = category.getCategoryName();
}

bool Category::operator==(const Category& other) const
{
	if (categoryName == other.categoryName)
	{
		return true;
	}
	else return false;
}

std::vector<Category> CategoryManager::categoryData;

void CategoryManager::AddCategory(std::string name)
{
	categoryData.push_back(Category(name));
}

void CategoryManager::AddCategory(Category category)
{
	categoryData.push_back(category);
}

const std::vector<Category>& CategoryManager::getAllCategoryData()
{
	return categoryData;
}

void CategoryManager::DeleteCategory(std::string categoryName)
{
	for (std::vector<Category>::iterator index = categoryData.begin(); index < categoryData.end(); index++)
	{
		if (categoryName == index->getCategoryName())
		{
			categoryData.erase(index);
			return;
		}
	}
}

void CategoryManager::DeleteCategory(Category category)
{
	for (std::vector<Category>::iterator index = categoryData.begin(); index < categoryData.end(); index++)
	{
		if ((*index) == category)
		{
			categoryData.erase(index);
			return;
		}
	}
}