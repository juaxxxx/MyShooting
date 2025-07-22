#include "pch.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "ResourceData.h"

void DataManager::Init()
{
	fs::path directory = fs::current_path() / L"../Resources/Data";

	{
		ResourceData* data = new ResourceData();
		loadDataObject(directory, ResourceData::Key(), data);
	}

	// Item.. 등 여러가지 로드
	{

	}
}

void DataManager::Destroy()
{
	for (auto iter : _datas)
	{
		SAFE_DELETE(iter.second);
	}
	_datas.clear();
}

void DataManager::loadDataObject(fs::path directory, string key, DataObject* obj)
{
	if (_datas.find(key) != _datas.end())
	{
		return;
	}

	fs::path path = directory / obj->GetFileName();
	ifstream file(path.c_str());
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open JSONfile", L"Error", MB_OK);
		return;
	}

	json data = json::parse(file);
	obj->Load(data);

	_datas.emplace(key, obj);
}
