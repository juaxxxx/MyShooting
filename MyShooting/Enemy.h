#pragma once

#include "UObject.h"

class Enemy : public UObject
{
public:
	Enemy() : _speed(100.0f), _angle(90), _FOV(0) {}
	~Enemy() override;
	void Init(float posX, float posY) override;
	void Init(Grid* grid) override;

	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	void OnColliderEnter();
	void OnColliderEnter(UObject* other) override;
	void Move(float deltaTime);
	void Attack();
	void OnDamaged();

private:
	float _speed;
	float _angle;
	float _FOV;
	Vector _convertPos;
};

