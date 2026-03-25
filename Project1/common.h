#pragma once
#include <random>

namespace RandomUtil {
	inline std::random_device rd;
	inline std::mt19937 gen(rd());
	
	int GetRange(int min, int max) 
	{
		std::uniform_int_distribution<int> uid(min, max);
		return uid(gen);
	}
}
