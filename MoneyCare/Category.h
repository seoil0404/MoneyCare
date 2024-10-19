#pragma once
#include <string>
#include <vector>

class Category
{
public:
	Category(std::string);
	Category(Category&);
	std::string getCategoryName();
	bool operator==(const Category&) const;
private:
	std::string categoryName;
};

class CategoryManager
{
public:
	static void AddCategory(std::string);
	static void AddCategory(Category);
	static const std::vector<Category>& getAllCategoryData();
	static void DeleteCategory(std::string);
	static void DeleteCategory(Category);
private:
	static std::vector<Category> categoryData;
};