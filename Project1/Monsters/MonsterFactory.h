#pragma once
#include "Common/common.h"
#include <memory>

class Monster;

class MonsterFactory
{
public:
	static std::unique_ptr<Monster> CreateMonster(MonsterType type, int level);
	static std::unique_ptr<Monster> RandomCreateMonster(int level);
};

