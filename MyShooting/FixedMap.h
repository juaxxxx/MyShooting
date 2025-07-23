#pragma once

#include "UObject.h"

class FixedMap : public UObject
{
public:
	FixedMap() {}
	~FixedMap() override {}
	void Init(float posX, float posY) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

private:
	float _speed;
};

