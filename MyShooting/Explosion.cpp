#include "pch.h"
#include "Explosion.h"
#include "UAnimator.h"
#include "UAnimation.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "GameScene.h"

void Explosion::Init(float posX, float posY)
{
	_pos = Vector(posX, posY);
	_animFrame = Vector(0, 0);
	_texture = ResourceManager::GetInstance()->GetTexture("Explosion");

	_anim = new UAnimator();
	_anim->CreateAnimation(L"Explosion", _texture, 2, 6, 12);
	_anim->ChangeAnimation(L"Explosion");
	_anim->GetAnimation()->CreateAnimation();
	_anim->SetOwner(this);
	_anim->GetAnimation()->Init(1);
}

void Explosion::Update(float deltaTime)
{
	GameScene* gameScene = GameScene::GetGameScene();
	if (gameScene == nullptr)
		return;

	_anim->Update(deltaTime);

	if (_anim->GetAnimation()->GetReps() == 0)
		gameScene->reserveDestroy(this);
}

void Explosion::Render(HDC hdc)
{
	if (_anim) _anim->Render(hdc);
	else
	{
		if (_texture) _texture->Render(hdc, _pos);
	}
}