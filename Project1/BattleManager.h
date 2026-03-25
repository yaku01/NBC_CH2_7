#pragma once
#include <vector>
#include <memory>

class Character;
class Monster;
class Item;

class BattleManager
{
public:
	BattleManager(Character* p);
	~BattleManager();

	void Release();

	void Init();
	void GenerateMonster(int level);
	void PlayerAttack(size_t target);
	void MonstersAttack();
	bool IsBattleOver();
	bool IsMonsterRemain();
	void DistributedReward();

	int GetMonsterSize() const;

private:
	Character* player = nullptr;
	std::vector<Monster*> monsters;
	std::vector<std::unique_ptr<Item>> items;
	int total_gold = 0;
	int total_exp = 0;
};

