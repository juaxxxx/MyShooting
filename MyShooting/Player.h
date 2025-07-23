#pragma once

#include "UObject.h"

class Player : public UObject
{
public:
	Player() { }
	~Player() override {}
	void Init(Grid* grid) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;
	void OnColliderEnter(UObject* other) override;
	void OnColliderEnter();
	void OnDamaged();
	void ClampPlayerPos();

	Vector GetForwardVector();
	uint32 GetHp() const { return _hp; }
private:
	float _speed;
	float _angle;
	float _FOV;
	uint32 _hp;
};

