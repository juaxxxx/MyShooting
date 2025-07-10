#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "TimerManager.h"
#include "ResourceManager.h"
#include "UIManager.h"

#include "GameScene.h"
#include "EditScene.h"

Game::~Game()
{
	if (_hdc)
	{
		::ReleaseDC(_hwnd, _hdc);
	}
	if (_bmpBack)
	{
		::DeleteObject(_bmpBack);
		_bmpBack = nullptr;
	}
	if (_hdcBack)
	{
		::DeleteDC(_hdcBack);
		_hdcBack = nullptr;
	}
}

void Game::Init(HWND hwnd)
{

	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);
	::GetClientRect(hwnd, &_rect);
	_hdcBack = ::CreateCompatibleDC(_hdc);
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	//::DeleteObject(prev);


	// Init
	InputManager::GetInstance()->Init(hwnd);
	TimeManager::GetInstance()->Init();
	ResourceManager::GetInstance()->Init();
	TimerManager::GetInstance()->Init();
	UIManager::GetInstance()->Init();

	// 시작씬은 게임으로 설정
	_currScene = new GameScene();
	_currScene->Init();

	// F1 키를 누르면, Edit Mode, F2 : GameMode
	//SAFE_DELETE(_currScene);
	//_currScene = new EditScene();
	//_currScene->Init();
}

void Game::Destroy()
{
	// Destroy
	InputManager::DestroyInstance();
	TimeManager::DestroyInstance();
	TimerManager::DestroyInstance();
	ResourceManager::GetInstance()->Destroy();
	UIManager::GetInstance()->DestroyInstance();

	if (_currScene)
	{
		_currScene->Destroy();
		SAFE_DELETE(_currScene);
	}
}

void Game::Update()
{
	InputManager::GetInstance()->Update();
	TimeManager::GetInstance()->Update();
	TimerManager::GetInstance()->Update(TimeManager::GetInstance()->GetDeltaTime());
	UIManager::GetInstance()->Update();
	if (_currScene)
	{
		_currScene->Update(TimeManager::GetInstance()->GetDeltaTime());
	}
}

void Game::Render()
{
	uint32 fps = TimeManager::GetInstance()->GetFps();
	float deltaTime = TimeManager::GetInstance()->GetDeltaTime();
	{
		//POINT mousePos = InputManager::GetInstance()->GetMousePos();
		//wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		//::TextOut(_hdcBack, 300, 10, str.c_str(), static_cast<int32>(str.size()));
	}
	{
		//wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		//::TextOut(_hdcBack, 5, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	if (_currScene)
	{
		_currScene->Render(_hdcBack);	
	}
	UIManager::GetInstance()->Render(_hdcBack);

	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
