#include "pch.h"
#include "Enemy.h"
#include "Missile.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "TimerManager.h"
#include "GameScene.h"
#include "Grid.h"

Enemy::~Enemy()
{
}

void Enemy::Init(float posX, float posY)
{
	_pos = Vector(posX, posY);
	_angle = DegreeToRadian(-90);
	_texture = ResourceManager::GetInstance()->GetTexture("Enemy1");
	_layer = LAYER_TYPE::ENEMY;

	// Colider Init
	_collider.radius = 20.0f;
	_collider.offset = POINT(0, 0);
	
	// 공격 반복 타이머 설정
	TimerManager::GetInstance()->AddTimer(10.0f, true, [this]() 
		{
			Attack(); 
		}
	);
}

void Enemy::Init(Grid* grid)
{
	_grid = grid;
	_gridpreX = PosToIndex(_pos.x);
	_gridpreY = PosToIndex(_pos.y);
	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
}

void Enemy::Update(float deltaTime)
{
	Move(deltaTime);

	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
	_grid->Move(this);
}

void Enemy::Render(HDC hdc)
{
	// 펜 생성
	HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
	int32 cellX = _gridX;
	int32 cellY = _gridY;


	// 라인 그리기
	MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX)*Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX)*Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX + 1) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX + 1) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY)*Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY)*Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY + 1) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY + 1) * Grid::CELL_SIZE);

	// 라인 그리기
	MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE, nullptr);
	LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 이전 펜 복원 및 새 펜 삭제
	SelectObject(hdc, oldPen);
	DeleteObject(myPen);

	// winAPI 텍스처 그릴때, 위치를 기준으로 텍스처를 그리는데, 이때도 똑같이 _pos 는 중심위치로 생각하면
	// 로직만들때 편하다.
	if (_texture)
	{
		_texture->Render(hdc, _pos);
	}
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크

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
				// 충돌 시
				// 피격 함수 호출
				OnDamaged();
				gameScene->RemoveMissile(dynamic_cast<Missile*>(objects[i]));
				break;
			}
		}
	}

}

void Enemy::OnColliderEnter(UObject* other)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	{
		if (nullptr == other) return;
		if (other->GetLayerType() == LAYER_TYPE::MISSILE)
		{
			Vector len = other->GetPos() - _pos;
			if (len.Length() < other->GetCollider().radius + _collider.radius)
			{
				// 충돌 시
				// 피격 함수 호출
				OnDamaged();
				gameScene->RemoveMissile(dynamic_cast<Missile*>(other));
			}
		}
	}
}


void Enemy::Move(float deltaTime)
{
	_pos.y += _speed * deltaTime;
	if (_pos.y >= 850.0f) _pos.y = -50.0f;
}

void Enemy::Attack()
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	Vector firePos;
	firePos.x = _pos.x;
	firePos.y = _pos.y + 30.0f;
	gameScene->CreateEnemyMissile(LAYER_TYPE::ENEMYMISSILE, firePos, _angle, ENEMY_TYPE::ENEMY1);

}

void Enemy::OnDamaged()
{
	GameScene* gameScene = GameScene::GetGameScene();

	gameScene->Instantiate(LAYER_TYPE::EFFECT, _pos);
	
	SetActive(false);
	gameScene->reserveDestroy(this);
}
