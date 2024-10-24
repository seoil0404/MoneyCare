#include "Json.h"

void JsonManager::FromJson(const nlohmann::json& json, std::vector<Layer>& layerData)
{
	layerData.resize(json.size());

	for (int index = 0; index < json.size(); index++) {
		FromJson(json[index], layerData[index]);
	}
}

void JsonManager::FromJson(const nlohmann::json& json, Layer& layer)
{
	FromJson(
		json[itemData()], 
		layer.getItemDataRef()
	);

	FromJson(
		json[budgetData()], 
		layer.getBudgetDataRef()
	);
}

void JsonManager::FromJson(const nlohmann::json& json, std::vector<Budget>& budgetData)
{
	budgetData.resize(json.size());

	for (int index = 0; index < json.size(); index++) {

		FromJson(
			json[index],
			budgetData[index]
		);
	}
	
}

void JsonManager::FromJson(const nlohmann::json& json, Budget& budget)
{
	FromJson(
		json,
		budget.getCategoryRef()
	);

	budget.getAmountRef() = json[amount()].get<int>();
}

void JsonManager::FromJson(const nlohmann::json& json, std::vector<Item>& itemData)
{
	itemData.resize(json.size());

	for (int index = 0; index < json.size(); index++) {

		FromJson(
			json[index],
			itemData[index]
		);

	}
}

void JsonManager::FromJson(const nlohmann::json& json, Item& item)
{
	item.setAmount(json[amount()].get<int>());
	item.setUsageName(json[usageName()].get<std::string>());

	FromJson(json, item.getCategoryRef());
}

void JsonManager::FromJson(const nlohmann::json& json, std::vector<Category>& categoryData)
{
	categoryData.resize(json.size());

	for (int index = 0; index < json.size(); index++) {
		FromJson(json[index], categoryData[index]);
	}
}

void JsonManager::FromJson(const nlohmann::json& json, Category& _category)
{
	_category.setCategoryName(json[category()].get<std::string>());
}