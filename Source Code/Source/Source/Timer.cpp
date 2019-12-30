#include "Timer.hpp"
#include <chrono>
#include <cmath>
namespace CommonUtilities
{
	Timer::Timer()
	{
		myCurrentFrame = myPreviousFrame = myFirstTime = std::chrono::high_resolution_clock::now();
		myDeltaTime = 0;
	};

	void Timer::Update()
	{
		myPreviousFrame = myCurrentFrame;
		myCurrentFrame = std::chrono::high_resolution_clock::now();
		myDeltaTime = (static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(myCurrentFrame - myPreviousFrame).count()) / 1000000);
	}

	const float Timer::GetDeltaTime() const
	{
		return myDeltaTime;
	}

	double Timer::GetTotalTime() const
	{
		return (static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(myCurrentFrame - myFirstTime).count()) / 1000000);
	}
}