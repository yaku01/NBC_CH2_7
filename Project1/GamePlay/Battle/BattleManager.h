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

    // ATB 처리
    void UpdateGauge(float delta_time, bool& player_turn, int& monster_turn);
    void ResetPlayerGauge();
    void SingleMonsterAttck(size_t idx);
    float GetPlayerGauge() const;
    float GetMonsterGauge(size_t idx) const;

private:
	std::vector<Monster*> monsters;
	std::vector<std::unique_ptr<IItem>> items;
	int total_gold = 0;
	int total_exp = 0;
    float player_gauge = 0.f;            // 행동력 게이지
    std::vector<float> monster_gauges;   // 몬스터 행동력 ㅔ이지
};

