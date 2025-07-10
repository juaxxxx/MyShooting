#include "pch.h"
#include "Enemy2.h"
#include "Missile.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "TimerManager.h"
#include "GameScene.h"

void Enemy2::Init(float posX, float posY)
{
	_pos = Vector(posX, posY);
	_angle = DegreeToRadian(-90);
	_texture = ResourceManager::GetInstance()->GetTexture("Enemy2");

	// Colider Init
	_collider.radius = 20.0f;
	_collider.offset = POINT(0, 0);

	// 공격 반복 타이머 설정
	TimerManager::GetInstance()->AddTimer(2.0f, true, [this]() {Attack(); });
}

void Enemy2::Update(float deltaTime)
{
	Move(deltaTime);
	OnColliderEnter();
}

void Enemy2::Render(HDC hdc)
{
	// winAPI 텍스처 그릴때, 위치를 기준으로 텍스처를 그리는데, 이때도 똑같이 _pos 는 중심위치로 생각하면
	// 로직만들때 편하다.
	if (_texture)
	{
		_texture->Render(hdc, _pos);
	}
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크
}

void Enemy2::OnColliderEnter()
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
				// 충돌 시
				// 피격 함수 호출
				OnDamaged();
				gameScene->RemoveMissile(dynamic_cast<Missile*>(objects[i]));
				break;
			}
		}
	}

}

void Enemy2::Move(float deltaTime)
{
	_pos.y += _speed * deltaTime;

	if (_pos.y >= 800) _pos.y = -50.0f;
}

void Enemy2::Attack()
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	Vector firePos;
	firePos.x = _pos.x;
	firePos.y = _pos.y + 30.0f;
	gameScene->CreateEnemyMissile(LAYER_TYPE::ENEMYMISSILE, firePos, _angle, ENEMY_TYPE::ENEMY2);
}

void Enemy2::OnDamaged()
{
	GameScene* gameScene = GameScene::GetGameScene();

	gameScene->Instantiate(LAYER_TYPE::EFFECT, _pos);

	gameScene->DestroyObject(this, LAYER_TYPE::ENEMY);
}
