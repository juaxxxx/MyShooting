#include "pch.h"
#include "Explosion.h"
#include "UAnimator.h"
#include "UAnimation.h"
#include "ResourceManager.h"
#include "TextureResource.h"

void Explosion::Init()
{
	_pos = Vector(200, 200);
	_animFrame = Vector(0, 0);
	_texture = ResourceManager::GetInstance()->GetTexture("Explosion");

	_anim = new UAnimator();
	_anim->CreateAnimation(L"Explosion", _texture, 2, 6, 12);
	_anim->ChangeAnimation(L"Explosion");
	_anim->GetAnimation()->CreateAnimation();
	_anim->SetOwner(this);
}

void Explosion::Update(float deltaTime)
{
	_anim->Update(deltaTime);
}

void Explosion::Render(HDC hdc)
{
	if (_anim) _anim->Render(hdc);
	else
	{
		if (_texture) _texture->Render(hdc, _pos);
	}
}