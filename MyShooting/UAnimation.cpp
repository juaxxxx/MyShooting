#include "pch.h"
#include "UAnimation.h"
#include "UAnimator.h"
#include "ResourceManager.h"
#include "TextureResource.h"
#include "UObject.h"
#include "ObjectPool.h"

void UAnimation::CreateAnimation()
{
	Frame frame{};

	uint32 cnt = 0;
	// �ִϸ��̼� �ؽ��� 1��� ������ ��ġ ������ ����.
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

void UAnimation::Init(int32 reps)
{
	_reps = reps;
}

void UAnimation::Update(float deltaTime)
{
	if (_reps == 0)
	{
		_canLoop = false;
		return;
	}

	_time += deltaTime;

	if (_time >= _gap)
	{
		if (_curFrameCount == _totalCount - 1)
		{
			_curFrameCount = 0;
			if (_reps != -1) _reps--;
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
	if (_canLoop && _texture) 
		_texture->Render(hdc, _animator->GetOwner()->GetPos(), GetCurFrame(), Vector(TEXTURE_SIZE, TEXTURE_SIZE));
}
