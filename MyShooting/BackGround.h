#pragma once

#include "UObject.h"

class Background : public UObject
{
public:
	void Init(float posX, float posY) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

private:
	float _speed;
};

