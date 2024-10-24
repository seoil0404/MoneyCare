#pragma once
#include <string>
#include <vector>

class Category
{
public:
	Category() { categoryName = "null"; };
	Category(std::string);
	Category(const Category&);
	
	std::string getCategoryName() const;
	
	void setCategoryName(std::string _categoryName) { categoryName = _categoryName; };

	bool operator==(const Category&) const;

private:
	std::string categoryName;
};

class CategoryManager
{
public:
	static void AddCategory(std::string);
	static void AddCategory(Category);

	static std::vector<Category>& getAllCategoryDataRef();
	static const std::vector<Category>& getAllCategoryData();
	
	static void DeleteCategory(const Category&);

private:
	static std::vector<Category> categoryData;
};