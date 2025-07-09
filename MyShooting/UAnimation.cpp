#include "pch.h"
#include "UAnimation.h"
#include "UAnimator.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "UObject.h"

void UAnimation::CreateAnimation()
{
	Frame frame{};

	uint32 cnt = 0;
	// 애니메이션 텍스쳐 1장당 프레임 위치 정보를 저장.
	for (int i = 0; i < _colCount; i++)
	{
		for (int j = 0; j < _count; j++)
		{
			frame.x = TEXTURE_SIZE * j;
			frame.y = TEXTURE_SIZE * i;
			frame.frameCount = cnt;

			_frames.push_back(frame);
			cnt++;
		}
	}
}

Vector UAnimation::GetCurFrame()
{
	return Vector(_frames[_curFrameCount].x, _frames[_curFrameCount].y);
}

void UAnimation::Init()
{
	// 애니메이션 바꿀 때 진행했던 값 초기화
}

void UAnimation::Update(float deltaTime)
{
	_time += deltaTime;

	if (_time >= _gap)
	{
		if (_curFrameCount == _totalCount - 1)
		{
			_curFrameCount = 0;
		}
		else
		{
			_curFrameCount++;
		}
		_time = 0;
	}

}

void UAnimation::Render(HDC hdc)
{
	if (_texture) _texture->Render(hdc, _animator->GetOwner()->GetPos(), GetCurFrame(), Vector(TEXTURE_SIZE, TEXTURE_SIZE));
}
