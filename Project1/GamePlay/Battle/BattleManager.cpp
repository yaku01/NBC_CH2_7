#include "BattleManager.h"
#include "Characters/Character.h"
#include "Monster.h"
#include "Items/Item.h"
#include "UI/UIManager.h"
#include "Common/common.h"
#include "Items/HealthPotion.h"
#include "Items/AttackBoost.h"


BattleManager::BattleManager(Character* p) : player(p)
{
}

BattleManager::~BattleManager()
{
}

void BattleManager::Release()
{
	for (auto& monster : monsters) {
		if (monster) {
			monster->SetVisible(false);
		}
	}

	monsters.clear();
}

void BattleManager::Init(const std::vector<Monster*>& monsters)
{
	this->monsters = monsters;
	total_exp = 0;
	total_gold = 0;
	items.clear();
}

void BattleManager::PlayerAttack(size_t target)
{
	if (!player || player->IsDead()) {
		return;
	}

	// 인덱스 유효성 검사
	if (target >= monsters.size()) {
		return;
	}
	
	Monster* monster = monsters[target];

	// 몬스터 유효성 검사
	if (!monster || monster->IsDead()) {
		return;
	}

	int damage = player->GetAttack();
	monster->TakeDamage(damage);
	
	UIManager::GetInstance().AddMessage(UIType::Log,
		"[공격] " + std::string(monster->GetName()) + "[" + std::to_string(target + 1) +
		"]에게 " + std::to_string(damage) + "데미지를 입혔습니다!");

	// 몬스터 사망 시
	if (monster->IsDead()) {
		
		// 보상 누적
		total_exp += 20;
		total_gold += RandomUtil::GetRange(10, 20);
		
		// [임시] 아이템 30퍼 확률로 지급
		if (RandomUtil::CheckProbability(30)) {
			items.push_back(std::make_unique<HealthPotion>());
		}

		monster->SetVisible(false);
	}
}

void BattleManager::MonstersAttack()
{
	if (!player || player->IsDead()) {
		return;
	}

	for (Monster* monster : monsters) {
		if (monster && !monster->IsDead()) {
			int damage = monster->GetAttack();
			player->TakeDamage(damage);

			UIManager::GetInstance().AddMessage(UIType::Log,
				"[피격] " + std::string(monster->GetName()) + "에게 " + std::to_string(damage) + "의 피해를 받았습니다!");

			if (player->IsDead()) {
				UIManager::GetInstance().AddMessage(UIType::Log,
					"[사망] " + std::string(monster->GetName()) + "에 의해 사망하였습니다...");
				break;
			}
		}
	}
}

bool BattleManager::IsBattleOver() const
{
	if (!player || player->IsDead()) {
		return true;
	}

	return IsPlayerWin();
}

bool BattleManager::IsPlayerWin() const
{
	for (const auto& monster : monsters) {
		if (monster && !monster->IsDead()) {
			return false;
		}
	}
	return true;
}

void BattleManager::DistributedReward()
{
	if (!player || player->IsDead()) {
		return;
	}

	player->GainExp(total_exp);
	player->GainGold(total_gold);

	UIManager::GetInstance().AddMessage(UIType::Log,
		"[보상] 경험치를 " + std::to_string(total_exp) + ", 골드를 " + std::to_string(total_gold) + "획득하였습니다!");


	for (auto& item : items) {
		UIManager::GetInstance().AddMessage(UIType::Log,
			"[보상] " + item->GetName() + "을 획득하였습니다!");

		player->AddItem(std::move(item));
	}
	items.clear();
}