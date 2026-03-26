#include "BattleScene.h"
#include "Core/GameManager.h"
#include "GamePlay/Battle/BattleManager.h"
#include "UI/UIManager.h"
#include "Monster.h"
#include "Characters/Character.h"

constexpr int MIN_MONSTER_COUNT = 1;
constexpr int MAX_MONSTER_COUNT = 3;

void BattleScene::Init()
{
	battle_manager = GameManager::GetInstance().GetBattleManager();

	int monster_count = RandomUtil::GetRange(MIN_MONSTER_COUNT, MAX_MONSTER_COUNT);
	for (int i = 0; i < monster_count; ++i) {
		monsters.push_back(new Monster());
	}

	if (!battle_manager || monsters.empty()) {
		PopScene();
		return;
	}

	battle_manager->Init(monsters);
	current_state = BattleState::Act;

	SetUI();
	SetMenu();
}

void BattleScene::SetUI()
{
}

void BattleScene::SetMenu()
{
	UIManager::GetInstance().ClearMessage(UIType::Menu);

	switch (current_state) {
	case BattleState::Act:
		UIManager::GetInstance().AddMessage(UIType::Menu, "1. 공격한다   2. 도망친다");
		UIManager::GetInstance().AddMessage(UIType::Menu, "전투 행동을 선택하세요: ");
		break;

	case BattleState::TargetEnemy:
	{
		std::string msg;
		for (size_t i = 0; i < monsters.size(); ++i) {
			if (monsters[i] && !monsters[i]->IsDead()) {
				msg += std::to_string(i + 1) + ". " + std::string(monsters[i]->GetName()) + "  ";
			}
		}
		msg += "0. 취소";

		UIManager::GetInstance().AddMessage(UIType::Menu, msg);
		UIManager::GetInstance().AddMessage(UIType::Menu, "공격할 대상을 선택하세요: ");
		break;
	}

	case BattleState::UseItem:
		// 아이템 사용 등 아군 선택
		break;
	}
}

void BattleScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	switch (current_state) {
	case BattleState::Act:
		ProcessActPhase(e.key_code);
		break;

	case BattleState::TargetEnemy:
		ProcessTargetPhase(e.key_code);
		break;

	case BattleState::UseItem:
		ProcessItemPhase(e.key_code);
		break;
	}
	SetMenu();
}

void BattleScene::Update(float delta_time)
{
}

void BattleScene::Render()
{
	
}

void BattleScene::Release()
{
	for (size_t i = 0; i < monsters.size(); ++i) {
		delete monsters[i];
		monsters[i] = nullptr;
	}
}

// private 함수
void BattleScene::ProcessActPhase(int key_code)
{
	switch (key_code) {
	case '1':
		current_state = BattleState::TargetEnemy;
		break;

	case '2':
		UIManager::GetInstance().AddMessage(UIType::Log, "[도망] 무사히 도망쳤습니다.");
		PopScene(); // 도망 -> 이전 씬(던전)으로 복귀!
		return;

	default:
		break;
	}
}

void BattleScene::ProcessTargetPhase(int key_code)
{
	if (key_code == '0') {
		current_state = BattleState::Act;
		return;
	}

	int idx = key_code - '1';

	if (idx >= 0 && idx < monsters.size() && !monsters[idx]->IsDead()) {
		// 플레이어 공격
		battle_manager->PlayerAttack(static_cast<size_t>(idx));

		// 몬스터 공격
		if (!battle_manager->IsBattleOver()) {
			battle_manager->MonstersAttack();
		}

		// 전투 종료 판단
		if (battle_manager->IsBattleOver()) {
			// 플레이어 사망으로 종료라면
			if (player->IsDead()) {
				UIManager::GetInstance().AddMessage(UIType::Log, "게임 오버! 타이틀로 돌아갑니다...");
				ChangeScene(SceneType::Title);
				return;
			}
			else {	// 플레이어 승리라면
				battle_manager->DistributedReward();
				PopScene();
				return;
			}
		}
		else {
			current_state = BattleState::Act;
			SetUI();
		}
	}
}

void BattleScene::ProcessItemPhase(int key_code)
{
}
