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
	// ���� ���� ����ϴ� UI �ٸ��� ����.
	void Init();
	void Update();
	void Render(HDC hdc);

private:
	GUI* _gui = nullptr;

};

