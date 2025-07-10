#pragma once

class UAnimator;

class UObject
{
public:
	UObject() {};
	virtual ~UObject();

	virtual void Init() {};
	virtual void Init(float posX, float posY, float angle, bool chase) {}; // Missile Init
	virtual void Init(float posX, float posY, float angle, ENEMY_TYPE type) {}; // EnemyMissile Init
	virtual void Init(float posX, float posY) {}; // Background Init
	
	virtual void Update(float deltaTime) {};
	virtual void Render(HDC hdc) {};
	virtual void OnColliderEnter() {}; // ±¸ÇöÀº Stay

	void SetPos(Vector pos) { _pos = pos; }
	void SetScale(Vector scale) { _scale = scale; }
	Vector GetPos() { return _pos; }
	Vector GetScael() { return _scale; }
	Collider GetCollider() { return _collider; }


protected:
	class TextureResource* _texture = nullptr;
	UAnimator* _anim = nullptr;
	Vector _animFrame;
	Vector _pos;
	Vector _scale;
	Collider _collider;
};

