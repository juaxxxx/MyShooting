#include "pch.h"
#include "TimerManager.h"
#include "Timer.h"

TimerManager::~TimerManager()
{
	for (auto iter = alarms.begin(); iter != alarms.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

void TimerManager::Init()
{

}
void TimerManager::Update(float deltaTime)
{
	for (auto iter = alarms.begin(); iter != alarms.end();)
	{
		if ((*iter)->Update(deltaTime))
		{
			iter = alarms.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}
void TimerManager::AddTimer(const float time, bool loop, function<void()> act)
{
	Timer* timer = new Timer(time, loop);
	timer->Act = act;
	alarms.push_back(timer);
}