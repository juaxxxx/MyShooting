#include "pch.h"
#include "Timer.h"

bool Timer::Update(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime >= _Goal)
	{
		Act();
		if (_loop)
		{
			_sumTime = 0;
		}
		else
		{
			return true;
		}
	}

	return false;
}