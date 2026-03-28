#include "MonsterFactory.h"
#include <unordered_map>
#include <functional>
#include "Orc.h"
#include "Slime.h"
#include "Troll.h"
#include "Goblin.h"

using Func = std::function<std::unique_ptr<Monster>(int)>;

std::unique_ptr<Monster> MonsterFactory::CreateMonster(MonsterType type, int level)
{
	static const std::unordered_map<MonsterType, Func> monster_creator = {
		{ MonsterType::Slime,	[](int level) { return std::make_unique<Slime>(level); }},
		{ MonsterType::Troll,	[](int level) { return std::make_unique<Troll>(level); }},
		{ MonsterType::Goblin,	[](int level) { return std::make_unique<Goblin>(level); }},
		{ MonsterType::Orc,		[](int level) { return std::make_unique<Orc>(level); }}
	};

	auto it = monster_creator.find(type);
	if (it != monster_creator.end()) {
		return it->second(level);
	}
	return nullptr;
}

std::unique_ptr<Monster> MonsterFactory::RandomCreateMonster(int level)
{
	int type = RandomUtil::GetRange(0, static_cast<int>(MonsterType::None) - 1);
	return CreateMonster(static_cast<MonsterType>(type), level);
}
