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
	// Game �ʿ� GetEnemy() �Լ��� �־��µ�,
	// GameScene ������ �̻縦 ����.
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	_pos.x += (_speed * ::cos(_angle) * deltaTime);
	_pos.y -= (_speed * ::sin(_angle) * deltaTime);

	// ȭ�� ���� ������� Ȯ���� �Ҹ�
	if (_pos.x < 0 || _pos.x >= GWinSizeX || _pos.y < 0 || _pos.y >= GWinSizeY)
	{
		// this ��ü�� delete �Ҹ��Ű�� ���� ���̻� ���� ó�� ���ϰ� ���� �����ϰ� ����
		gameScene->RemoveMissile(this);
		return;
	}

	// �پ��� ������Ʈ�� �������� ������.
}

void Missile::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _pos);
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // �ݶ��̴� ���� üũ
}
