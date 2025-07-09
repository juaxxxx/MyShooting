#pragma once
#include "Scene.h"

class UObject;

class GameScene : public Scene
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float deltatTime) override;
	virtual void Render(HDC hdc) override;
	void DestroyObject(UObject* object, LAYER_TYPE layer);

	static GameScene* GetGameScene();

public:
	void CreateMissile(float posX, float posY, float angle, bool chase);
	void RemoveMissile(class Missile* missile);
	vector<UObject*> GetObjects(LAYER_TYPE layerType) { return _objects[(uint32)layerType]; }
	//class Enemy* GetEnemy() { return _enemy; }

private:
	// 게임 안 객체 관리
	vector<UObject*> _objects[(uint32)LAYER_TYPE::END];
};

