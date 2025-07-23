#include "pch.h"
#include "EnemyMissile.h"
#include "Game.h"
#include "Enemy.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Camera.h"

void EnemyMissile::Init(float posX, float posY, float angle, ENEMY_TYPE type)
{
	_pos = Vector(posX, posY);
	_angle = angle;
	_type = type;

	// Colider Init
	_collider.radius = 5.0f;
	_collider.offset = POINT(0, 0);
	_layer = LAYER_TYPE::ENEMYMISSILE;

	_texture = ResourceManager::GetInstance()->GetTexture("EnemyBullet");
}

void EnemyMissile::Init(Grid* grid)
{
	_grid = grid;
	_gridpreX = PosToIndex(_pos.x);
	_gridpreY = PosToIndex(_pos.y);
	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
}

void EnemyMissile::Update(float deltaTime)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	_pos.x += (_speed * ::cos(_angle) * deltaTime);
	_pos.y -= (_speed * ::sin(_angle) * deltaTime);

	Vector cameraPos = Camera::GetCameraPos();
	// 화면 밖을 벗어났는지 확인후 소멸
	if (_pos.x < cameraPos.x - (GWinSizeX / 2) ||
		_pos.x >= cameraPos.x + (GWinSizeX / 2) ||
		_pos.y < cameraPos.y - (GWinSizeY / 2) ||
		_pos.y >= cameraPos.y + (GWinSizeY / 2))
	{
		gameScene->reserveDestroy(this);
		return;
	}

	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
	_grid->Move(this);
}

void EnemyMissile::Render(HDC hdc)
{
	if (_texture)
	{
		switch (_type)
		{
		case ENEMY_TYPE::ENEMY1:
		{
			_texture->Render(hdc, _pos, Vector(0, 0), Vector(8, 8));
			break;
		}
		case ENEMY_TYPE::ENEMY2:
		{
			_texture->Render(hdc, _pos, Vector(8, 0), Vector(8, 8));
			break;
		}
		case ENEMY_TYPE::ENEMY3:
		{
			_texture->Render(hdc, _pos, Vector(16, 0), Vector(8, 8));
			break;
		}
		case ENEMY_TYPE::ENEMY4:
		{
			_texture->Render(hdc, _pos, Vector(24, 0), Vector(8, 8));
			break;
		}
		}
	}
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크
}
