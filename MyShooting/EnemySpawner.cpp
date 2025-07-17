#include "pch.h"
#include "EnemySpawner.h"
#include "GameScene.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Enemy2.h"

void EnemySpawner::Init(float ttime)
{
	srand(time(0));

	_time = ttime;
	SpawnSetUp();
}

void EnemySpawner::Update(float deltaTime)
{
	_timer += deltaTime;

	if (_timer >= _time)
	{
		SpawnSetUp();
		_timer = 0;
	}
}



void EnemySpawner::SpawnSetUp()
{

	uint32 randPosX = rand() % 400 + 30; // 30 ~ 430
	uint32 randPosY = rand() % 100; // -100 ~ 0
	uint32 randfreq = rand() % 3 + 5;
	//ENEMY_TYPE type = (ENEMY_TYPE)(rand() % 2);
	ENEMY_TYPE type = ENEMY_TYPE::ENEMY1;

	TimerManager::GetInstance()->AddTimer(randfreq, true, [this, randPosX, randPosY, type]() {SpawnEnemy(Vector(randPosX, randPosY), type); });
}

void EnemySpawner::SpawnEnemy(Vector pos, ENEMY_TYPE type)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	Vector gap(rand() % 50 - 100, 0);
	gameScene->Instantiate(type, pos + gap);
}
