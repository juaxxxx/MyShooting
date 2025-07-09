#pragma once

#include "UObject.h"

class Enemy : public UObject
{
public:
	void Init(float posX, float posY) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	void OnColliderEnter() override;
	void Attack();
	void OnDamaged();

private:
	float _speed;
	float _angle;
	float _FOV;
};

