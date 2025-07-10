#pragma once

#include "UObject.h"

class EnemySpawner : public UObject 
{
public:
	EnemySpawner() : _time(0), _timer(0) {};
	~EnemySpawner() {};
	void Init(float time);
	void Update(float deltaTime);

	void SpawnSetUp();
	void SpawnEnemy(Vector pos, ENEMY_TYPE type);
private:
	float _time;
	float _timer;
};

