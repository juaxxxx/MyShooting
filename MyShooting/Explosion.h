#pragma once

#include "UObject.h"

class Explosion : public UObject
{
public:
	Explosion() {}
	~Explosion() override {}

	void Init(float posX, float posY) override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

};