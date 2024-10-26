#pragma once
#include <nlohmann/json.hpp>
#include "DataManager.h"

class JsonManager
{
public:
	static void LoadData(std::vector<Layer>&, std::vector<Category>&);
	static void SaveData(const std::vector<Layer>&, const std::vector<Category>&);

protected:
	static void ToJson(nlohmann::json&, const std::vector<Layer>&);
	static void ToJson(nlohmann::json&, const Layer&);
	static void ToJson(nlohmann::json&, const std::vector<Budget>&);
	static void ToJson(nlohmann::json&, const Budget&);
	static void ToJson(nlohmann::json&, const std::vector<Item>&);
	static void ToJson(nlohmann::json&, const Item&);
	static void ToJson(nlohmann::json&, const std::vector<Category>&);
	static void ToJson(nlohmann::json&, const Category&);

	static void FromJson(const nlohmann::json&, std::vector<Layer>&);
	static void FromJson(const nlohmann::json&, Layer&);
	static void FromJson(const nlohmann::json&, std::vector<Budget>&);
	static void FromJson(const nlohmann::json&, Budget&);
	static void FromJson(const nlohmann::json&, std::vector<Item>&);
	static void FromJson(const nlohmann::json&, Item&);
	static void FromJson(const nlohmann::json&, std::vector<Category>&);
	static void FromJson(const nlohmann::json&, Category&);

private:
	static std::string itemData()	{ return "itemData"; };
	static std::string budgetData() { return "budgetData"; };
	static std::string category()	{ return "category"; };
	static std::string usageName()	{ return "usageName"; };
	static std::string amount()		{ return "amount"; };

	static std::string userUsageData() { return "userUsageData"; };
	static std::string userCategoryData() { return "userCategoryData"; };
	
	static std::string jsonFilePath() { return "userData.json"; };

	static nlohmann::json LoadJsonFile();
	static void	SaveJsonFile(const nlohmann::json&);
};