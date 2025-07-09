#pragma once

class Timer
{
public:
	Timer(float goal, bool loop) : _sumTime(0), _Goal(goal), _loop(loop), Act(nullptr) {};

	bool Update(float deltaTime);

	float _sumTime;
	float _Goal;
	bool _loop;
	function<void()> Act;
};