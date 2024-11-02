#include "Json.h"
#include "DebugLog.h"
#include <fstream>

void JsonManager::LoadData(std::vector<Layer>& layer, std::vector<Category>& category)
{
	nlohmann::json json = LoadJsonFile();
	
	FromJson(json[userUsageData()], layer);
	FromJson(json[userCategoryData()], category);

	Debug::Log("DEBUG: All JSON data from the file has been loaded.");
}

void JsonManager::SaveData(const std::vector<Layer>& layer, const std::vector<Category>& category)
{
	nlohmann::json json;

	ToJson(json[userUsageData()], layer);
	ToJson(json[userCategoryData()], category);

	SaveJsonFile(json);

	Debug::Log("DEBUG: JSON data has been saved to the file.");
}

nlohmann::json JsonManager::LoadJsonFile()
{
	nlohmann::json json;

	std::ifstream file(jsonFilePath());

	if (!file.is_open())
	{
		Debug::Log("DEBUG: No file!");
		std::ofstream makeFile(jsonFilePath());
		JsonManager::SaveData(DataManager::getAllLayerRef(), CategoryManager::getAllCategoryDataRef());
		makeFile.close();
		
		file.open(jsonFilePath());
	}
	
	file >> json;
	file.close();
	
	return json;
}

void JsonManager::SaveJsonFile(const nlohmann::json& json)
{
	std::ofstream file(jsonFilePath());

	file << json.dump(4);
	file.close();
}