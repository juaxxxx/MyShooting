#include "pch.h"
#include "GameScene.h"
#include "UObject.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"
#include "Game.h"
#include "BackGround.h"
#include "Explosion.h"

void GameScene::Init()
{
	// 플레이어 생성. 플레이어는 하나 뿐이기 때문에 _objects[(uint32)LAYER_TYPE::PLAYER]][0] 으로 해도 되려나
	{
		Player* object = new Player();
		object->Init();
		_objects[(uint32)LAYER_TYPE::PLAYER].push_back(object);
	}
	// 적 생성
	{
		Enemy* object = new Enemy();
		object->Init(100, 100);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
	}
	{
		Enemy* object = new Enemy();
		object->Init(200, 100);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
	}
	{
		Enemy* object = new Enemy();
		object->Init(300, 100);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
	}
	{
		Enemy* object = new Enemy();
		object->Init(400, 100);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
	}
	// 배경 생성
	{
		Background* object = new Background();
		object->Init(GWinSizeX / 2, 400.0f);
		_objects[(uint32)LAYER_TYPE::BACKGROUND].push_back(object);
	}
	{
		Background* object = new Background();
		object->Init(GWinSizeX / 2, -400.0f);
		_objects[(uint32)LAYER_TYPE::BACKGROUND].push_back(object);
	}
	{
		Explosion* object = new Explosion();
		object->Init();
		_objects[(uint32)LAYER_TYPE::EFFECT].push_back(object);
	}
}

void GameScene::Destroy()
{
	for (int i = 0; i < (uint32)LAYER_TYPE::END; i++)
	{
		for (int j = 0; j < _objects[i].size(); j++)
		{
			SAFE_DELETE(_objects[i][j]);
		}
		_objects[i].clear();
	}
}

void GameScene::Update(float deltaTime)
{
	for (int i = 0; i < (uint32)LAYER_TYPE::END; i++)
	{
		for (int j = 0; j < _objects[i].size(); j++)
		{
			if (_objects[i][j])
			{
				_objects[i][j]->Update(deltaTime);
			}
		}
	}
}

void GameScene::Render(HDC hdc)
{
	for (int i = 0; i < (uint32)LAYER_TYPE::END; i++)
	{
		for (int j = 0; j < _objects[i].size(); j++)
		{
			if (_objects[i][j])
			{
				_objects[i][j]->Render(hdc);
			}
		}
	}
}

void GameScene::DestroyObject(UObject* object, LAYER_TYPE layer)
{
	for (auto iter = _objects[(uint32)layer].begin(); iter != _objects[(uint32)layer].end();)
	{
		if (*iter == object)
		{
			SAFE_DELETE(*iter);
			_objects[(uint32)layer].erase(iter);
			return;
		}
		else
		{
			iter++;
		}
	}
}

GameScene* GameScene::GetGameScene()
{
	return dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrScene());
}


void GameScene::CreateMissile(float posX, float posY, float angle, bool chase)
{
	Missile* missile = new Missile();
	missile->Init(posX, posY, angle, chase);
	_objects[(uint32)LAYER_TYPE::MISSILE].push_back(missile);
}

void GameScene::RemoveMissile(Missile* missile)
{
	auto it = std::find(_objects[(uint32)LAYER_TYPE::MISSILE].begin(), _objects[(uint32)LAYER_TYPE::MISSILE].end(), missile);
	_objects[(uint32)LAYER_TYPE::MISSILE].erase(it);

	// 객체도 소멸한다.
	// 객체의 생성과 소멸은 모두 Game이라는 매니저가 총괄
	// 이 코드는 괜찮을까요? 위험한 코드를 만들어야 하네.... 나중에 한번 고민해보자.TODO
	delete missile;
}
