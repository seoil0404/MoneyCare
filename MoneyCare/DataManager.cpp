#include "DataManager.h"
#include "DebugLog.h"

void DataManager::AddLayer(Layer layer)
{
	layerData.push_back(layer);
}

const std::vector<Layer>& DataManager::getAllLayer()
{
	return layerData;
}

std::vector<Layer>& DataManager::getAllLayerRef()
{
	return layerData;
}

Layer& DataManager::getLayer(std::vector<Layer>::iterator index)
{
	return (*index);
}

Layer& DataManager::getRecentLayer()
{
	if (IsEmpty()) {
		Debug::Log("Error: Attempted to access a layer that does not exist.\n");
	}
	return layerData.back();
}

bool DataManager::IsEmpty()
{
	if (layerData.size() <= 0)
	{
		return true;
	}

	return false;
}

int DataManager::getLayerDataSize()
{
	return (int)layerData.size();
}