#include "pch.h"
#include "EnemyMissile.h"
#include "Game.h"
#include "Enemy.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"

void EnemyMissile::Init(float posX, float posY, float angle, ENEMY_TYPE type)
{
	_pos = Vector(posX, posY);
	_angle = angle;
	_type = type;

	// Colider Init
	_collider.radius = 5.0f;
	_collider.offset = POINT(0, 0);

	_texture = ResourceManager::GetInstance()->GetTexture("EnemyMISSILE");
}

void EnemyMissile::Update(float deltaTime)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	_pos.x += (_speed * ::cos(_angle) * deltaTime);
	_pos.y -= (_speed * ::sin(_angle) * deltaTime);

	// 화면 밖을 벗어났는지 확인후 소멸
	if (_pos.x < 0 || _pos.x >= GWinSizeX || _pos.y < 0 || _pos.y >= GWinSizeY)
	{
		gameScene->reserveDestroy(this);
		return;
	}

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
