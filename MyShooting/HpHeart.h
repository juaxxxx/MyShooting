#pragma once

#include "UObject.h"

class HpHeart : public UObject
{
public:
	HpHeart() {}
	~HpHeart() {}
	virtual void Init(float posX, float posY) override; // Background Init
	//virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

};

