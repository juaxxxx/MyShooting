#include "pch.h"
#include "UAnimator.h"
#include "UAnimation.h"
#include "ResourceManager.h"
#include "TextureResource.h"

UAnimator::~UAnimator()
{
	for (auto iter : _anims)
	{
		SAFE_DELETE(iter.second);
	}
	_anims.clear();
}

void UAnimator::Play()
{
}

// 애니메이터에 애니메이션 저장.
void UAnimator::CreateAnimation(wstring name, TextureResource* texture, uint32 colcount, uint32 framecount, uint32 totalcount)
{
	UAnimation* anim = new UAnimation(name, this, texture, colcount, framecount, totalcount);
	_anims.insert(make_pair(name, anim));
}

void UAnimator::ChangeAnimation(wstring name)
{
	if (_anims.find(name) == _anims.end()) return;

	_curAnim = _anims[name];
}

void UAnimator::Update(float deltaTime)
{
	_curAnim->Update(deltaTime);
}

void UAnimator::Render(HDC hdc)
{
	_curAnim->Render(hdc);
}
