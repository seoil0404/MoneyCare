#include "DataManager.h"
#include "DebugLog.h"

std::vector<Layer> DataManager::layerData;

void Layer::AddItem(Item item)
{
	itemData.push_back(item);

	if (!CheckCategoryAllocation(item.getCategory()))
	{
		AddBudgetData(item.getCategory());
	}
}

void Layer::DeleteItem(std::vector<Item>::iterator iterator)
{
	itemData.erase(iterator);
}

int Layer::getBudgetValue(const Category& category)
{
	for (Budget index : budgetData)
	{
		if (index.getCategory() == category)
		{
			return index.getAmount();
		}
	}

	Debug::Log("Error: Attempted to access a budget that does not exist.\n");
	return NULL;
}

void Layer::AddBudgetData(Category category, int value)
{
	budgetData.push_back(Budget(category, value));
}

void Layer::setBudgetValue(Category category, int value)
{
	if (!CheckCategoryAllocation(category)) {
		Debug::Log("Error: Attempted to access a category that does not exist.\n");
		return;
	}
	else
	{
		for (Budget& index : budgetData)
		{
			if (index.getCategory() == category)
			{
				index.setAmount(value);
				return;
			}
		}
	}
}

bool Layer::CheckCategoryAllocation(Category category)
{
	for (Budget index : budgetData)
	{
		if (index.getCategory() == category)
		{
			return true;
		}
	}
	return false;
}

std::pair<int, int> Layer::getTotalAmountInCategory(const Category& category)
{
	int positiveAmount = 0;
	int negativeAmount = 0;
	
	for (Item index : itemData)
	{
		if (index.getCategory() == category)
		{
			int tempAmount = index.getAmount();
			
			if (tempAmount > 0) positiveAmount += tempAmount;
			else				negativeAmount += tempAmount;
		}
	}

	return std::pair<int, int>(positiveAmount, negativeAmount);
}

Budget Layer::getNextBudget(Category category)
{
	for (int index = 0; index < budgetData.size() - 1; index++)
	{
		if (category == budgetData[index].getCategory())
		{
			return budgetData[index + 1];
		}
	}
	return budgetData.front();
}