#include "pch.h"
#include "Enemy.h"
#include "Missile.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "TimerManager.h"
#include "GameScene.h"

void Enemy::Init(float posX, float posY)
{
	_pos = Vector(posX, posY);
	_angle = DegreeToRadian(-90);
	_texture = ResourceManager::GetInstance()->GetTexture("Enemy1");

	// Colider Init
	_collider.radius = 20.0f;
	_collider.offset = POINT(0, 0);
	
	// ���� �ݺ� Ÿ�̸� ����
	TimerManager::GetInstance()->AddTimer(2.0f, true, [this]() {Attack(); });
}

void Enemy::Update(float deltaTime)
{
	OnColliderEnter();
}

void Enemy::Render(HDC hdc)
{
	// winAPI �ؽ�ó �׸���, ��ġ�� �������� �ؽ�ó�� �׸��µ�, �̶��� �Ȱ��� _pos �� �߽���ġ�� �����ϸ�
	// �������鶧 ���ϴ�.
	if (_texture)
	{
		_texture->Render(hdc, _pos);
	}
	::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // �ݶ��̴� ���� üũ

}

void Enemy::OnColliderEnter()
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	{
		vector<UObject*> objects = gameScene->GetObjects(LAYER_TYPE::MISSILE);
		for (int i = 0; i < objects.size(); i++)
		{
			Vector len = objects[i]->GetPos() - _pos;
			if (len.Length() < objects[i]->GetCollider().radius + _collider.radius)
			{
				// �浹 ��
				// �ǰ� �Լ� ȣ��
				OnDamaged();
				gameScene->RemoveMissile(dynamic_cast<Missile*>(objects[i]));
				break;
			}
		}
	}

}

void Enemy::Attack()
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	Vector firePos;
	firePos.x = _pos.x;
	firePos.y = _pos.y + 30.0f;
	gameScene->CreateMissile(firePos.x, firePos.y, _angle, false);
}

void Enemy::OnDamaged()
{
	GameScene* gameScene = GameScene::GetGameScene();
	
	gameScene->DestroyObject(this, LAYER_TYPE::ENEMY);
}
