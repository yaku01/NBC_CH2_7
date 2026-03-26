#pragma once
#define NOMINMAX

#include <random>


namespace RandomUtil {
	inline std::random_device rd;
	inline std::mt19937 gen(rd());
	
	inline int GetRange(int min, int max) 
	{
		std::uniform_int_distribution<int> uid(min, max);
		return uid(gen);
	}

	inline bool CheckProbability(int percent)
	{
		int probability = GetRange(1, 100);
		return probability <= percent;
	}

	inline bool CheckProbability(double percent)
	{
		std::uniform_real_distribution<double> urd(1.0, 100.0);
		double probability = urd(gen);
		return probability <= percent;
	}
}

enum class UIType {
	Menu,
	Log,
	COUNT
};

enum class EventType {
	KeyDown,
	KeyUp,
	ChangeScene,	// »õ·Î¿î ¾ÀÀ¸·Î ÀüÈ¯
	PushScene,		// ÇöÀç ¾ÀÀ» ¸ØÃß°í »õ·Î¿î ¾À ¶ç¿ò
	PopScene,		// ÇöÀç ¾À ²ô°í ¾Æ·¡¿¡ ÀÖ´ø ¾ÀÀ¸·Î º¹±Í
	Quit
};

enum class SceneOp { Change, Push, Pop, None };

enum class SceneType {
	Title,
	Town,
	Dungeon,
	Battle,
	None
};

struct Event {
	EventType type;

	// °°Àº ¸Þ¸ð¸® °ø°£À» °ãÃÄ¼­ »ç¿ë
	union {
		int key_code;
		SceneType next_scene;
	};
};
