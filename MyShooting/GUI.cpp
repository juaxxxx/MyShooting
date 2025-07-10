#include "pch.h"
#include "GUI.h"
#include "HpHeart.h"
#include "GameOverText.h"

GUI::~GUI()
{
	SAFE_DELETE(_hpHeart);
	SAFE_DELETE(_gameoverText);
}

void GUI::Init()
{
	_hpHeart = new HpHeart();
	_hpHeart->Init(70, 780);
	_gameoverText = new GameOverText();
	_gameoverText->Init(220, 400);
}

void GUI::Render(HDC hdc)
{
	_hpHeart->Render(hdc);
	_gameoverText->Render(hdc);
}
