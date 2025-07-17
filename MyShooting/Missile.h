#pragma once

#include "UObject.h"

class Missile : public UObject
{
public:
	Missile() {}
	~Missile() override;
	void Init(float posX, float posY, float angle, bool chase) override;
	void Init(Grid* grid) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;


private:
	float _speed = 400;
	float _angle = 0;
	bool _chase = false;
};

