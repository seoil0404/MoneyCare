#pragma once
#include "Category.h"
#include <vector>

// A piece of Layer
class Item
{
public:
	Item() { amount = 0; usageName = "null"; };
	Item(int _amount, std::string _usageName, const Category& _category) : category(_category), usageName(_usageName), amount(_amount) {};
	
	Category getCategory() const { return category; }
	int getAmount() const { return amount; }
	std::string getUsageName() const { return usageName; }

	Category& getCategoryRef() { return category; }

	void setAmount(int _amount) { amount = _amount; }
	void setUsageName(std::string _usageName) { usageName = _usageName; }
	void setCategory(Category _category) { category = _category; }

private:
	int amount;
	std::string usageName;
	Category category;
};

// A piece of Layer
class Budget
{
public:
	Budget() : category(), amount() {};
	Budget(Category _category, int _amount) : category(_category), amount(_amount) {};
	
	Category getCategory() const	{ return category; };
	int getAmount() const			{ return amount; };
	
	Category& getCategoryRef()		{ return category; }
	int& getAmountRef()				{ return amount; }
	
	void setAmount(int _amount)		{ amount = _amount; };

private:
	Category category;
	int amount;
};

// A piece of DataManager
class Layer
{
public:
	Layer() { };

	void AddItem(Item);
	void DeleteItem(std::vector<Item>::iterator);

	void setBudgetValue(Category, int);
	int getBudgetValue(const Category&);

	// first = positiveAmount , second = negativeAmount
	std::pair<int, int> getTotalAmountInCategory(const Category&);

	const std::vector<Item>& getItemData() const { return itemData; };
	const std::vector<Budget>& getBudgetData() const { return budgetData; };

	std::vector<Item>& getItemDataRef() { return itemData; };
	std::vector<Budget>& getBudgetDataRef() { return budgetData; };
	
	Budget getNextBudget(Category);

protected:
	bool CheckCategoryAllocation(Category);

	void AddBudgetData(Category, int = 0);

private:
	std::vector<Item> itemData;
	std::vector<Budget> budgetData;
};

class DataManager
{
public:
	static void AddLayer(Layer = Layer());
	
	static const std::vector<Layer>& getAllLayer();
	static std::vector<Layer>& getAllLayerRef();

	static Layer& getLayer(std::vector<Layer>::iterator);
	static Layer& getRecentLayer();
	
	static int getLayerDataSize();
	
	// return true when data is empty.
	static bool IsEmpty();
	
private:
	static std::vector<Layer> layerData;
};