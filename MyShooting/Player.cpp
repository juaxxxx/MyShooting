#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "InputManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"

void Player::Init()
{
	// Player 정보 초기화
	_pos = Vector(100, 100);
	_speed = 300.0f;
	_angle = DegreeToRadian(90);
	_FOV = DegreeToRadian(60);

	// Colider Init
	_collider.radius = 10.0f;
	_collider.offset = POINT(0, 0);

	_texture = ResourceManager::GetInstance()->GetTexture("Player");
}

void Player::Update(float deltaTime)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	// W 키가 눌러졌으면 위로 이동.
	// S 키가 눌러졌으면 아래로 이동.
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::W))
	{
		_pos.y -= (deltaTime * _speed);
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::S))
	{
		_pos.y += (deltaTime * _speed);
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::A))
	{
		_pos.x -= (deltaTime * _speed);
	}
	if (InputManager::GetInstance()->GetButtonPressed(KeyType::D))
	{
		_pos.x += (deltaTime * _speed);
	}

	if (InputManager::GetInstance()->GetButtonDown(KeyType::SpaceBar))
	{
		Vector firePos;
		firePos.x = _pos.x + ::cos(_angle) * 30;
		firePos.y = _pos.y - ::sin(_angle) * 30;

		gameScene->CreateMissile(firePos.x, firePos.y, _angle, false);
	}

	OnColliderEnter();
}

void Player::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _pos);
	::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크
}

void Player::OnColliderEnter()
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

void Player::OnDamaged()
{
	GameScene* gameScene = GameScene::GetGameScene();

	gameScene->DestroyObject(this, LAYER_TYPE::PLAYER);
}

Vector Player::GetForwardVector()
{
	Vector playerPos = _pos;
	Vector firePos;
	firePos.x = _pos.x + ::cos(_angle) * 50;
	firePos.y = _pos.y - ::sin(_angle) * 50;

	Vector dir = firePos - playerPos;
	dir.Normalize();

	return dir;
}
