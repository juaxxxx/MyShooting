#pragma once
#include "Scene.h"

class UObject;
class Grid;

class GameScene : public Scene
{
public:
	GameScene() {}
	~GameScene();
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void Render(HDC hdc) override;
	void DestroyObject();
	void reserveDestroy(UObject* object);
	static GameScene* GetGameScene();

public:
	virtual void Instantiate(LAYER_TYPE type, Vector pos) override;
	void Instantiate(ENEMY_TYPE type, Vector pos);
	void CreateEnemyMissile(LAYER_TYPE type, Vector pos, float angle, ENEMY_TYPE enemytype);
	void CreateMissile(float posX, float posY, float angle, bool chase);

	void RemoveMissile(class Missile* missile);

	vector<UObject*> GetObjects(LAYER_TYPE layerType) { return _objects[(uint32)layerType]; }
	UObject* GetPlayer();
	Grid* GetGrid() { return _gameGrid; }

private:
	// 게임 안 객체 관리
	vector<UObject*> _objects[(uint32)LAYER_TYPE::END];
	vector<UObject*> _reserveobjects;
	Grid* _gameGrid = nullptr;
};

