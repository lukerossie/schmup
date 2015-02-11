#pragma once
#include "SDLW/SDLW.hpp"
class Clock
{
	private:
	
	public:
	int FPS;
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point oldclock;
	high_resolution_clock::time_point dclock;
	long long lapsedMilli;
	long long milliseconds;
	long long microseconds;
	int FPStimer;
	int FPScounter;
	Clock();
	void update();
};
