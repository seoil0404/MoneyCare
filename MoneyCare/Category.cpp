#include "Category.h"

std::string Category::getCategoryName() const
{
	return categoryName;
}

Category::Category(std::string name)
{
	categoryName = name;
}

Category::Category(const Category& category)
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

std::vector<Category>& CategoryManager::getAllCategoryDataRef()
{
	return categoryData;
}

const std::vector<Category>& CategoryManager::getAllCategoryData()
{
	return categoryData;
}

void CategoryManager::DeleteCategory(const Category& category)
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

Category CategoryManager::getNextCategory(Category category)
{
	for (int index = 0; index < categoryData.size(); index++)
	{
		if (categoryData[index] == category)
		{
			if (index + 1 < categoryData.size())
			{
				return categoryData[index + 1];
			}
			else return categoryData.front();
		}
	}
	return categoryData.front();
}