#include "pch.h"
#include "UIManager.h"
#include "GUI.h"

UIManager::~UIManager()
{
	SAFE_DELETE(_gui);
}

void UIManager::Init()
{
	_gui = new GUI();
	_gui->Init();
}

void UIManager::Update()
{
}

void UIManager::Render(HDC hdc)
{
	_gui->Render(hdc);
}
