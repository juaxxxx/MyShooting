#pragma once

#include "UObject.h"

class Player : public UObject
{
public:
	Player() {};
	~Player() {};
	void Init() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	void OnColliderEnter() override;
	void OnDamaged();

	Vector GetForwardVector();

private:
	float _speed;
	float _angle;
	float _FOV;
};

