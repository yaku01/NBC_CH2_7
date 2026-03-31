#include "BattleManager.h"
#include "Characters/Character.h"
#include "Monsters/Monster.h"
#include "Items/Item.h"
#include "UI/UIManager.h"
#include "Common/common.h"
#include "Items/ItemFactory.h"
#include "Core/LogManager.h"

BattleManager::BattleManager() = default;
BattleManager::~BattleManager() = default;

void BattleManager::Release()
{
	for (auto& monster : monsters) {
		if (monster) {
			monster->SetActive(false);
		}
	}

	monsters.clear();
}

void BattleManager::Init(const std::vector<std::unique_ptr<Monster>>& monsters)
{
	this->monsters.clear();
	for (const auto& monster : monsters) {
		this->monsters.push_back(monster.get());
	}

	total_exp = 0;
	total_gold = 0;
	items.clear();
}

void BattleManager::PlayerAttack(size_t target)
{
	auto& player = Character::GetInstance();
	if (player.IsDead()) {
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

	int damage = player.GetTotalAttack();
	monster->TakeDamage(damage);
	
	LogManager::GetInstance().AddLog(
		"[공격] " + std::string(monster->GetName()) + "[" + std::to_string(target + 1) +
		"]에게 " + std::to_string(damage) + "데미지를 입혔습니다!"); 

	// 몬스터 사망 시
	if (monster->IsDead()) {
		
		// 킬보드에 킬 추가
		LogManager::GetInstance().AddKill(monster->GetName());

		// 보상 누적
		total_exp += 20;
		total_gold += RandomUtil::GetRange(10, 20);
		
		// 아이템 드롭테이블에서 받아와서 추가
		auto item_ids = monster->GetDropItems();
		for (const auto& item_id : item_ids) {
			auto item = ItemFactory::CreateItem(item_id);
			if (item) {
				items.push_back(std::move(item));
			}
		}

		monster->SetActive(false);
	}
}

void BattleManager::MonstersAttack()
{
	auto& player = Character::GetInstance();
	if (player.IsDead()) {
		return;
	}

	for (Monster* monster : monsters) {
		if (monster && !monster->IsDead()) {
			int damage = monster->GetAttack();
			player.TakeDamage(damage);

			LogManager::GetInstance().AddLog(
				"[피격] " + std::string(monster->GetName()) + "에게 " + std::to_string(damage) + "의 피해를 받았습니다!");

			if (player.IsDead()) {
				LogManager::GetInstance().AddLog(
					"[사망] " + std::string(monster->GetName()) + "에 의해 사망하였습니다...");
				break;
			}
		}
	}
}

bool BattleManager::IsBattleOver() const
{
	auto& player = Character::GetInstance();
	if (player.IsDead()) {
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
	auto& player = Character::GetInstance();
	if (player.IsDead()) {
		return;
	}

	player.GainExp(total_exp);
	player.GainGold(total_gold);

	LogManager::GetInstance().AddLog(
		"[보상] 경험치를 " + std::to_string(total_exp) + ", 골드를 " + std::to_string(total_gold) + "획득하였습니다!");


	for (auto& item : items) {
		LogManager::GetInstance().AddLog(
			"[보상] " + item->GetName() + "을 획득하였습니다!");

		player.AddItem(std::move(item));
	}
	items.clear();
}
