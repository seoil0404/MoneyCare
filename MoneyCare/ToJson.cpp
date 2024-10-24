#include "Json.h"

void JsonManager::ToJson(nlohmann::json& json, const std::vector<Layer>& layerData)
{
	for (int index = 0; index < layerData.size(); index++) {

		ToJson(
			json[index],
			layerData[index]
		);
	}
}

void JsonManager::ToJson(nlohmann::json& json, const Layer& layer)
{
	ToJson(
		json[itemData()],
		layer.getItemData()
	);

	ToJson(
		json[budgetData()],
		layer.getBudgetData()
	);
}

void JsonManager::ToJson(nlohmann::json& json, const std::vector<Budget>& budgetData)
{
	for (int index = 0; index < budgetData.size(); index++) {

		ToJson(
			json[index],
			budgetData[index]
		);
	}
}

void JsonManager::ToJson(nlohmann::json& json, const Budget& budget)
{
	ToJson(
		json,
		budget.getCategory()
	);

	json[amount()] = budget.getAmount();
}

void JsonManager::ToJson(nlohmann::json& json, const std::vector<Item>& itemData)
{
	for (int index = 0; index < itemData.size(); index++) {

		ToJson(
			json[index],
			itemData[index]
		);
	}
}

void JsonManager::ToJson(nlohmann::json& json, const Item& item)
{
	json[amount()] = item.getAmount();
	json[usageName()] = item.getUsageName();

	ToJson(
		json,
		item.getCategory()
	);
}

void JsonManager::ToJson(nlohmann::json& json, const std::vector<Category>& _categoryData)
{
	for (int index = 0; index < _categoryData.size(); index++) {

		ToJson(
			json[index],
			_categoryData[index]
		);
	}
}

void JsonManager::ToJson(nlohmann::json& json, const Category& _category)
{
	json[category()] = _category.getCategoryName();
}