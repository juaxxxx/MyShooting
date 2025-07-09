#pragma once

#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
	friend Singleton<TimeManager>;

private:
	TimeManager() {}

public:
	void Init();
	void Update();

	uint32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64 _frequency = 0;	// CPU 클럭
	uint64 _prevCount = 0;

	// 이전프레임과 현재 프레임 사이의 시간 가격
	float _deltaTime = 0.f;

private:

	// 초당 몇 프레임인지
	uint32 _frameCount = 0;
	float _frameTime = 0.f;
	uint32 _fps = 0;
};

