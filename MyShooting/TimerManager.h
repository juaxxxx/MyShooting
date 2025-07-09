#pragma once

#include "Singleton.h"

class TimerManager : public Singleton<TimerManager>
{
public:
	TimerManager(){}
	~TimerManager();
	void Init();
	void Update(float deltaTime);
	void AddTimer(const float time, bool loop, function<void()> act);

	vector<class Timer*> alarms;
};

