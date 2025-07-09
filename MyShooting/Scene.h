#pragma once

// �� ����� �����Ѵ�.
// LobbyScene, EditScene, GameScene, ChracterSelectScene
class Scene
{
public:
	virtual void Init() {}
	virtual void Destroy() {};
	virtual void Update(float deltatTime) {}
	virtual void Render(HDC hdc) {}
	virtual void OnColliderEnter(LAYER_TYPE otherType, function<void()> act) {};
};

