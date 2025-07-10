#pragma once

#include "UObject.h"

class Enemy2 : public UObject
{
public:
	Enemy2() : _speed(100.0f), _angle(90), _FOV(0) {}
	~Enemy2() override {}
	void Init(float posX, float posY) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	void OnColliderEnter() override;
	void Move(float deltaTime);
	void Attack();
	void OnDamaged();

private:
	float _speed;
	float _angle;
	float _FOV;
};

