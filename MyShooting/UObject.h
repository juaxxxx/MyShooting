#pragma once

class UAnimator;
#include "Grid.h"

class UObject
{
	friend class Grid;

public:
	UObject() {};
	virtual ~UObject();

	virtual void Init() {};
	virtual void Init(Grid* grid) {};
	virtual void Init(float posX, float posY, float angle, bool chase) {}; // Missile Init
	virtual void Init(float posX, float posY, float angle, ENEMY_TYPE type) {}; // EnemyMissile Init
	virtual void Init(float posX, float posY) {}; // Background Init
	
	virtual void Update(float deltaTime) {};
	virtual void Render(HDC hdc) {};
	virtual void OnColliderEnter(UObject* other) {}; // ±¸ÇöÀº Stay

	void SetPos(Vector pos) { _pos = pos; }
	void SetScale(Vector scale) { _scale = scale; }
	Vector GetPos() { return _pos; }
	Vector GetScael() { return _scale; }
	Collider GetCollider() { return _collider; }
	LAYER_TYPE GetLayerType() { return _layer; }
	int32 PosToIndex(float pos);
	int32 PosToIndex(float pos, bool IsX);
	void SetActive(bool active) { _active = active; }
	bool GetActive() { return _active; }


protected:
	class TextureResource* _texture = nullptr;
	UAnimator* _anim = nullptr;
	Vector _animFrame;
	Vector _pos;
	Vector _scale;
	Collider _collider;
	Grid* _grid;
	int32 _gridX;
	int32 _gridY;
	int32 _gridpreX;
	int32 _gridpreY;
	bool _active = true;
	LAYER_TYPE _layer = LAYER_TYPE::DEFAULT;
};

