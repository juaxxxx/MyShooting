#pragma once

// �� ����� �����Ѵ�.
// LobbyScene, EditScene, GameScene, ChracterSelectScene
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Init() {}
	virtual void Destroy() {};
	virtual void Update(float deltatTime) {}
	virtual void Render(HDC hdc) {}
	virtual void OnColliderEnter(LAYER_TYPE otherType, function<void()> act) {};

	virtual void Instantiate(LAYER_TYPE type, Vector pos) {};

protected:
	virtual void loadResource() {}

};

