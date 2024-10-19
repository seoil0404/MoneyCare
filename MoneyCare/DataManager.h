#pragma once
#include "Category.h"
#include <vector>

// Financial Item
class FinItem
{
public:
	FinItem(int _amount, Category& category) : categoryData(category), amount(_amount) {};
private:
	Category categoryData;
	int amount;
};

class Layer
{
public:
private:
	std::vector<FinItem> finItemData;
	std::vector<std::pair<Category, int>> budgetData;
};

class DataManager
{
public:
private:
	static std::vector<Layer> layerData;
};