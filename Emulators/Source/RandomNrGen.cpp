#include <random>
#include "RandomNrGen.hpp"

namespace CommonUtilities
{
	
	int GenerateRandomNr(int aMin, int aMax)
	{
		std::random_device seed;
		std::mt19937 rndEngine(seed());

		std::uniform_int_distribution<int> rndDist(aMin, aMax);
		return rndDist(rndEngine);
	}

	float GenerateRandomNr(float aMin, float aMax)
	{
		std::random_device seed;
		std::mt19937 rndEngine(seed());

		std::uniform_real_distribution<float> rndDist(aMin, aMax);
		float test = rndDist(rndEngine);
		return test;
	}
}