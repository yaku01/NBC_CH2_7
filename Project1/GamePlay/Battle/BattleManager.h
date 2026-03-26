#pragma once
#include <vector>
#include <memory>

class Character;
class Monster;
class IItem;

class BattleManager
{
public:
	BattleManager(Character* p);
	~BattleManager();

	void Release();

	void Init(const std::vector<Monster*>& monsters);
	void PlayerAttack(size_t target);
	void MonstersAttack();
	bool IsBattleOver() const;
	bool IsPlayerWin() const;
	void DistributedReward();

private:
	Character* player = nullptr;
	std::vector<Monster*> monsters;
	std::vector<std::unique_ptr<IItem>> items;
	int total_gold = 0;
	int total_exp = 0;
};

