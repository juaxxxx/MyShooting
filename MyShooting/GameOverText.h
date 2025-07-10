#pragma once

#include "UObject.h"

class GameOverText : public UObject
{
public:
	GameOverText() {};
	~GameOverText() {};

	virtual void Init(float posX, float posY) override; // Background Init
	//virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;
};

