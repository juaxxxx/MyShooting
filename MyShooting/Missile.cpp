#include "pch.h"
#include "Missile.h"
#include "Game.h"
#include "Enemy.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"

void Missile::Init(float posX, float posY, float angle, bool chase)
{ 
	_pos = Vector(posX, posY);
	_angle = angle;
	_chase = chase;

	// Colider Init
	_collider.radius = 5.0f;
	_collider.offset = POINT(0, 0);
	
	_texture = ResourceManager::GetInstance()->GetTexture("PlayerMISSILE");
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

	// 화면 밖을 벗어났는지 확인후 소멸
	if (_pos.x < 0 || _pos.x >= GWinSizeX || _pos.y < 0 || _pos.y >= GWinSizeY)
	{
		// this 객체가 delete 소멸시키고 나서 더이상 로직 처리 못하게 냅다 리턴하고 ㅌㅌ
		gameScene->RemoveMissile(this);
		return;
	}

	// 다양한 업데이트가 있을수도 있지만.
}

void Missile::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _pos);
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크
}
