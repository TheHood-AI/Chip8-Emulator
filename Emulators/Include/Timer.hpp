#pragma once
#include <chrono>
#include <array>
namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer();
		Timer(const Timer& aTimer) = delete;
		Timer& operator=(const Timer& aTimer) = delete;
		void Update();
		const float GetDeltaTime() const;
		double GetTotalTime() const;
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> myCurrentFrame;
		std::chrono::time_point<std::chrono::high_resolution_clock> myFirstTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> myPreviousFrame;
		std::chrono::high_resolution_clock myTimer;
		float myDeltaTime;
	};
}