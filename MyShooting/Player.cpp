#include "pch.h"
#include "Player.h"
#include "Game.h"
#include "InputManager.h"
#include "Enemy.h"
#include "Missile.h"
#include "EnemyMissile.h"
#include "GameScene.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Grid.h"
#include "Camera.h"

void Player::Init(Grid* grid)
{
	// Player 정보 초기화
	_grid = grid;
	_pos = Vector(400, 9300);
	_gridpreX = PosToIndex(_pos.x);
	_gridpreY = PosToIndex(_pos.y);
	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
	
	_speed = 300.0f;
	_angle = DegreeToRadian(90);
	_FOV = DegreeToRadian(60);
	_hp = 3;
	_layer = LAYER_TYPE::PLAYER;

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


	_gridX = PosToIndex(_pos.x);
	_gridY = PosToIndex(_pos.y);
	_grid->Move(this);
}

void Player::Render(HDC hdc)
{
	// 펜 생성
	HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
	
	//Vector convert = Camera::ConvertScreenPos(Vector(_gridX, _gridY));

	int32 cellX = _gridX;
	int32 cellY = _gridY;
	//Vector convertPos = Camera::ConvertScreenPos(_pos);

	//int32 cellX = PosToIndex(convertPos.x);
	//int32 cellY = PosToIndex(convertPos.y);
	auto convertGridPos = [cellX, cellY, this](HDC hdc, int32 offsetX_1, int32 offsetY_1, int32 offsetX_2, int32 offsetY_2)
		{
			int32 x1 = (cellX + offsetX_1) * Grid::CELL_SIZE;
			int32 y1 = (cellY + offsetY_1) * Grid::CELL_SIZE;

			Vector convert1 = Camera::ConvertScreenPos(Vector(x1, y1));

			MoveToEx(hdc, convert1.x, convert1.y, nullptr);

			int32 x2 = (cellX + offsetX_2) * Grid::CELL_SIZE;
			int32 y2 = (cellY + offsetY_2) * Grid::CELL_SIZE;

			Vector convert2 = Camera::ConvertScreenPos(Vector(x2, y2));

			LineTo(hdc, convert2.x, convert2.y);
		};
	
	// 라인 그리기
	convertGridPos(hdc, -1, -1, -1, 2);
	//MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, 0, -1, 0, 2);
	//MoveToEx(hdc, (cellX) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, 1, -1, 1, 2);
	//MoveToEx(hdc, (cellX + 1)*Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX + 1)*Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, 2, -1, 2, 2);
	//MoveToEx(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, -1, -1, 2, -1);
	//MoveToEx(hdc, (cellX - 1)*Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX + 2)*Grid::CELL_SIZE, (cellY - 1) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, -1, 0, 2, 0);
	//MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, -1, 1, 2, 1);
	//MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY + 1) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY + 1) * Grid::CELL_SIZE);

	// 라인 그리기
	convertGridPos(hdc, -1, 2, 2, 2);
	//MoveToEx(hdc, (cellX - 1) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE, nullptr);
	//LineTo(hdc, (cellX + 2) * Grid::CELL_SIZE, (cellY + 2) * Grid::CELL_SIZE);

	// 이전 펜 복원 및 새 펜 삭제
	SelectObject(hdc, oldPen);
	DeleteObject(myPen);

	if (_texture) _texture->Render(hdc, _pos);
	//::Ellipse(hdc, _pos.x - _collider.radius, _pos.y - _collider.radius, _pos.x + _collider.radius, _pos.y + _collider.radius); // 콜라이더 범위 체크
}

void Player::OnColliderEnter()
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	{
		vector<UObject*> objects = gameScene->GetObjects(LAYER_TYPE::ENEMYMISSILE);
		for (int i = 0; i < objects.size(); i++)
		{
			Vector len = objects[i]->GetPos() - _pos;
			if (len.Length() < objects[i]->GetCollider().radius + _collider.radius)
			{
				// 충돌 시
				// 피격 함수 호출
				OnDamaged();
				gameScene->reserveDestroy(this);
				break;
			}
		}
	}
}

void Player::OnColliderEnter(UObject* other)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	{
		if (other->GetLayerType() == LAYER_TYPE::ENEMYMISSILE)
		{
			Vector len = other->GetPos() - _pos;
			if (len.Length() < other->GetCollider().radius + _collider.radius)
			{
				// 충돌 시
				// 피격 함수 호출
				OnDamaged();
				gameScene->RemoveMissile(dynamic_cast<EnemyMissile*>(other));
			}
		}
	}
}


void Player::OnDamaged()
{
	GameScene* gameScene = GameScene::GetGameScene();

	gameScene->Instantiate(LAYER_TYPE::EFFECT, _pos);

	_hp--;

	if (_hp <= 0)
		gameScene->reserveDestroy(this);
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
