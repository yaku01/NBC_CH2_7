#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "common.h"

#include <iostream>

constexpr int MIN_MONSTER_COUNT = 1;
constexpr int MAX_MONSTER_COUNT = 3;

BattleManager::BattleManager(Character* p)
{
	player = p;
}

BattleManager::~BattleManager()
{
}

void BattleManager::Release()
{
	monsters.clear();
}

void BattleManager::Init()
{
	monsters.clear();
	total_exp = 0;
	total_gold = 0;
	items.clear();
}

void BattleManager::GenerateMonster(int level)
{
	// min~max 마리의 몬스터 랜덤 생성
	//int count = RandomUtil::GetRange(MIN_MONSTER_COUNT, MAX_MONSTER_COUNT);
	int count = 3;
	for (int i = 0; i < count; ++i) {
		monsters.emplace_back(new Monster());
	}
	// 나중에 오브젝트 풀링 적용
}

void BattleManager::PlayerAttack(size_t target)
{
	if (!player) {
		return;
	}

	// 인덱스 유효성 검사
	if (target >= monsters.size()) {
		return;
	}
	
	Monster* monster = monsters[target];
	if (!monster) {	// 몬스터 유효성 검사
		return;
	}

	monster->TakeDamage(player->GetAttack());
	std::cout << target << " 번 몬스터 공격, 데미지 : " << player->GetAttack() << std::endl;

	// 몬스터 사망 시
	if (monster->GetHealth() <= 0) {
		
		// 보상 누적
		total_exp += 20;
		total_gold += RandomUtil::GetRange(10, 20);
		// 아이템 드롭

		monsters[target] = nullptr;
	}
}

void BattleManager::MonstersAttack()
{
	if (!player || player->GetHp() <= 0) {
		return;
	}

	for (size_t i = 0; i < monsters.size(); ++i) {
		if (monsters[i]) {
			player->TakeDamage(monsters[i]->GetAttack());

			if (player->GetHp() <= 0) {
				// 사망처리

				break;
			}
		}
	}
}

bool BattleManager::IsBattleOver()
{
	if (!player || player->GetHp() <= 0) {
		return true;
	}

	return !IsMonsterRemain();
}

bool BattleManager::IsMonsterRemain()
{
	for (size_t i = 0; i < monsters.size(); ++i) {
		if (monsters[i]) {
			return true;
		}
	}
	return false;
}

void BattleManager::DistributedReward()
{
	if (!player || player->GetHp() <= 0) {
		return;
	}

	player->GainExp(total_exp);
	player->GainGold(total_gold);

	// 아이템 지급처리
	// --
}

int BattleManager::GetMonsterSize() const
{
	return static_cast<int>(monsters.size());
}
