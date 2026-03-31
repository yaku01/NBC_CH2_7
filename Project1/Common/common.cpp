#include "common.h"
#include <random>
#include <algorithm>

namespace {
	std::random_device rd;
	std::mt19937 gen(rd());
}

namespace RandomUtil{
	int GetRange(int min, int max) 
	{
		std::uniform_int_distribution<int> uid(min, max);
		return uid(gen);
	}

	bool IsSuccess(double probability)
	{
		std::uniform_real_distribution<double> urd(0.0, 1.0);
		return urd(gen) < probability;
	}

	void Shuffle(std::vector<int>& v)
	{
		std::shuffle(v.begin(), v.end(), gen);
	}
}

