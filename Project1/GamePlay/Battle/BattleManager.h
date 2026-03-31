#pragma once
#include <vector>
#include <memory>

class IItem;
class Monster;
class IItem;

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

	void Release();

	void Init(const std::vector<std::unique_ptr<Monster>>& monsters); 
	void PlayerAttack(size_t target);
	void MonstersAttack();
	bool IsBattleOver() const;
	bool IsPlayerWin() const;
	void DistributedReward();

private:
	std::vector<Monster*> monsters;
	std::vector<std::unique_ptr<IItem>> items;
	int total_gold = 0;
	int total_exp = 0;
};

