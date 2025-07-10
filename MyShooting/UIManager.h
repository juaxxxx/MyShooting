#pragma once

#include "Singleton.h"

class GUI;

class UIManager : public Singleton<UIManager>
{
	friend Singleton<UIManager>;

private:
	UIManager(){}
	~UIManager();
public:
	// 씬에 따라 사용하는 UI 다르게 구현.
	void Init();
	void Update();
	void Render(HDC hdc);

private:
	GUI* _gui = nullptr;

};

