#include "clock.hpp"

Clock::Clock()
{
	milliseconds = 0;
	microseconds = 0;
	lapsedMilli = 0;
	start = high_resolution_clock::now();
	oldclock = high_resolution_clock::now();
	FPStimer = 0;
	FPS = 0;
	FPScounter = 0;			
}
void Clock::update()
{
	auto dclock = high_resolution_clock::now() - oldclock;
	oldclock = high_resolution_clock::now();
	lapsedMilli = duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
	microseconds = duration_cast<std::chrono::microseconds>(dclock).count();
	milliseconds = duration_cast<std::chrono::milliseconds>(dclock).count();
	FPStimer += milliseconds;
	FPScounter++;
	if(FPStimer > 1000)
	{
		FPS = FPScounter;
		FPScounter = 0;
		FPStimer = 0;
	}
}
