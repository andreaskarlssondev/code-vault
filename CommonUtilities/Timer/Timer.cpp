#include "pch.h"
#include "framework.h"
#include "Timer.h"
#include <chrono>

#define currentTime std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()

namespace CommonUtilities
{

	Timer::Timer() : myDeltaTime(0.0f)
	{
		// Startime req for total time
		myStartTime = currentTime;
		myPrevTime = myStartTime;
	}

	void Timer::Update()
	{
		double myCurrentTime = currentTime;
		// Delta (elapsed) Time since last called
		myDeltaTime = static_cast<float>(myCurrentTime - myPrevTime);
		myPrevTime = myCurrentTime;
	}

	double Timer::GetTotalTime() const
	{
		return currentTime - myStartTime;
	}

}