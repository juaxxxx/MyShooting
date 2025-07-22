#pragma once

#include "UObject.h"

class EnemyMissile : public UObject
{
public:
	EnemyMissile() {}
	~EnemyMissile() override {}
	void Init(float posX, float posY, float angle, ENEMY_TYPE type) override;
	void Init(Grid* grid);
	void Update(float deltaTime) override;
	void Render(HDC hdc) override;

private:
	ENEMY_TYPE _type;
	float _speed = 400;
	float _angle = 0;
	bool _chase = false;
};

