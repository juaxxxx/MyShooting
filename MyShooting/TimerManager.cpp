#include "pch.h"
#include "TimerManager.h"
#include "Timer.h"

TimerManager::~TimerManager()
{
	for (auto iter = alarms.begin(); iter != alarms.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
	alarms.clear();
	newalarms.clear();
}

void TimerManager::Init()
{

}
void TimerManager::Update(float deltaTime)
{
	alarms = newalarms;
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
	newalarms.push_back(timer);
}
