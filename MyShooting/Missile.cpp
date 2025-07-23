#include "pch.h"
#include "Missile.h"
#include "Game.h"
#include "Enemy.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Grid.h"
#include "Camera.h"

Missile::~Missile()
{
}

void Missile::Init(float posX, float posY, float angle, bool chase)
{ 
	_pos = Vector(posX, posY);
	_angle = angle;
	_speed = 1000.f;
	_chase = chase;
	_layer = LAYER_TYPE::MISSILE;

	// Colider Init
	_collider.radius = 5.0f;
	_collider.offset = POINT(0, 0);
	
	_texture = ResourceManager::GetInstance()->GetTexture("PlayerBullet");
}

void Missile::Init(Grid* grid)
{
	_grid = grid;
	_gridpreX = PosToIndex(_pos.x);
	_gridpreY = PosToIndex(_pos.y);
	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
}

void Missile::Update(float deltaTime)
{
	// Game 쪽에 GetEnemy() 함수가 있었는데,
	// GameScene 하위로 이사를 갔다.
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
		// this 객체가 delete 소멸시키고 나서 더이상 로직 처리 못하게 냅다 리턴하고 ㅌㅌ
		gameScene->RemoveMissile(this);
		return;
	}

	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
	_grid->Move(this);
}

void Missile::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _pos);
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크
}
