#pragma once

#include "UObject.h"

class Explosion : public UObject
{
public:
	Explosion() {};
	~Explosion() {};

	void Init() override;
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

};