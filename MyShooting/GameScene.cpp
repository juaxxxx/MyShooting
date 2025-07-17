#include "pch.h"
#include "GameScene.h"
#include "UObject.h"
#include "Player.h"
#include "Missile.h"
#include "EnemyMissile.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Game.h"
#include "BackGround.h"
#include "Explosion.h"
#include "EnemySpawner.h"
#include "Grid.h"

GameScene::~GameScene()
{

}

void GameScene::Init()
{
	{
		_gameGrid = new Grid();
	}
	{
		Player* object = new Player();
		object->Init(_gameGrid);
		_objects[(uint32)LAYER_TYPE::PLAYER].push_back(object);
	}
	{
		EnemySpawner* object = new EnemySpawner();
		object->Init(5.0f);
		_objects[(uint32)LAYER_TYPE::ENEMYSPAWNER].push_back(object);
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
	SAFE_DELETE(_gameGrid);
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
	_gameGrid->Update();
	DestroyObject();
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
	_gameGrid->Render(hdc);
}

void GameScene::Instantiate(LAYER_TYPE type, Vector pos)
{
	switch (type)
	{
	case LAYER_TYPE::BACKGROUND:

		break;
	case LAYER_TYPE::EFFECT:
	{
		Explosion* object = new Explosion();
		object->Init(pos.x, pos.y);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
		break;
	}
	case LAYER_TYPE::ENEMY:
	{
		break;
	}
	case LAYER_TYPE::MISSILE:
	{
		break;
	}
	case LAYER_TYPE::PLAYER:
		
		break;
	case LAYER_TYPE::END:
		
		break;
	default:
		
		break;
	}
}

void GameScene::Instantiate(ENEMY_TYPE type, Vector pos)
{
	switch (type)
	{
	case ENEMY_TYPE::ENEMY1:
	{
		Enemy* object = new Enemy();
		object->Init(pos.x, pos.y);
		object->Init(_gameGrid);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
		break;
	}
	case ENEMY_TYPE::ENEMY2:
	{
		Enemy2* object = new Enemy2();
		object->Init(pos.x, pos.y);
		_objects[(uint32)LAYER_TYPE::ENEMY].push_back(object);
		break;
	}
	}
}

void GameScene::DestroyObject()
{
	for (auto iter = _reserveobjects.begin(); iter != _reserveobjects.end(); iter++)
	{
		if ((*iter)->GetLayerType() == LAYER_TYPE::ENEMY)
		{
			auto obj = find(_objects[(int32)LAYER_TYPE::ENEMY].begin(), _objects[(int32)LAYER_TYPE::ENEMY].end(), (*iter));

			SAFE_DELETE(*obj);
			_objects[(int32)LAYER_TYPE::ENEMY].erase(obj);
		}

		if ((*iter)->GetLayerType() == LAYER_TYPE::MISSILE)
		{
			auto obj = find(_objects[(int32)LAYER_TYPE::MISSILE].begin(), _objects[(int32)LAYER_TYPE::MISSILE].end(), (*iter));

			SAFE_DELETE(*obj);
			_objects[(int32)LAYER_TYPE::MISSILE].erase(obj);
		}
	}

	_reserveobjects.clear();
}

void GameScene::reserveDestroy(UObject* object)
{
	_reserveobjects.push_back(object);
}

GameScene* GameScene::GetGameScene()
{
	return dynamic_cast<GameScene*>(Game::GetInstance()->GetCurrScene());
}

void GameScene::CreateEnemyMissile(LAYER_TYPE type, Vector pos, float angle, ENEMY_TYPE enemytype)
{
	EnemyMissile* missile = new EnemyMissile();
	missile->Init(pos.x, pos.y, angle, enemytype);
	_objects[(uint32)LAYER_TYPE::ENEMYMISSILE].push_back(missile);
}

void GameScene::CreateMissile(float posX, float posY, float angle, bool chase)
{
	Missile* missile = new Missile();
	missile->Init(posX, posY, angle, chase);
	missile->Init(_gameGrid);
	_objects[(uint32)LAYER_TYPE::MISSILE].push_back(missile);
}

void GameScene::RemoveMissile(Missile* missile)
{
	missile->SetActive(false);
	reserveDestroy(missile);
}

UObject* GameScene::GetPlayer()
{
	if (_objects[(uint32)LAYER_TYPE::PLAYER].size() == 0) return nullptr;
	else return _objects[(uint32)LAYER_TYPE::PLAYER][0];
}
