#include "BattleScene.h"
#include "Core/GameManager.h"
#include "GamePlay/Battle/BattleManager.h"
#include "UI/UIManager.h"
#include "UI/GameUI.h"
#include "Characters/Character.h"
#include "Core/DungeonMapState.h"
#include "Monsters/Monster.h"
#include "Monsters/MonsterFactory.h"
#include "Core/LogManager.h"
#include "Core/SaveLoadManager.h"


constexpr int MIN_MONSTER_COUNT = 1;
constexpr int MAX_MONSTER_COUNT = 3;
constexpr int INTENSITY = 1;
constexpr float DURATION = 0.3f;


BattleScene::BattleScene() = default;
BattleScene::~BattleScene() = default;

void BattleScene::Init()
{
	battle_manager = GameManager::GetInstance().GetBattleManager();
    player_turn = false;
    monster_turn_idx = -1;

	int monster_count = 1;
	if (is_boss_battle) {
		monsters.push_back(MonsterFactory::CreateMonster(MonsterType::Boss, Character::GetInstance().GetLevel()));
	}
	else {
		monster_count = RandomUtil::GetRange(MIN_MONSTER_COUNT, MAX_MONSTER_COUNT);
		for (int i = 0; i < monster_count; ++i) {
			monsters.push_back(MonsterFactory::RandomCreateMonster(Character::GetInstance().GetLevel()));
		}
	}

	if (!battle_manager || monsters.empty()) {
		PopScene();
		return;
	}

	battle_manager->Init(monsters);
	current_state = BattleState::Wait;

	// -----------
	//배경
	auto bg = std::make_unique<AsciiUI>(0, 0);
	bg->LoadAsciiArt("Resource/Battle_Background.txt");
	scene_uis.push_back(std::move(bg));


	int center = 20;
	// ----------------
	// 플레이어 아스키 아트  x : 5, y : 20
	player_ui = std::make_unique<BattleUnitUI>(5, center);
	player_ui->LoadAsciiArt("Resource/Player.txt"); 

	// 몬스터 아스키 아트
	int diff = 15;
	std::vector<int> position;
	position.reserve(MAX_MONSTER_COUNT);
	
	// 몬스터 마리수 별 배치
	switch (monster_count) { 
	case 1:
		position = { center };
		break;

	case 2:
		position = { center - diff / 2 - 1, center + diff / 2 + 1 }; 
		break;

	case 3:
		position = { center - diff, center, center + diff };
		break;
	}


	for (int i = 0; i < monster_count; ++i) {
		auto monster_ui = std::make_unique<BattleUnitUI>(45, position[i]);
		monster_ui->LoadAsciiArt(monsters[i]->GetAsciiArtPath());
		monster_uis.push_back(std::move(monster_ui));
	}
	// ----------------

	SetMenu();
}

void BattleScene::SetMenu()
{
	UIManager::GetInstance().ClearContent(UIType::Menu);

	switch (current_state) {
    case BattleState::Wait:
        UIManager::GetInstance().AddContent(UIType::Menu, "턴을 기다리는 중입니다...");
        break;

	case BattleState::Act:
		UIManager::GetInstance().AddContent(UIType::Menu, "1. 공격한다   0. 도망친다");
		UIManager::GetInstance().AddContent(UIType::Menu, "전투 행동을 선택하세요: ");
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

		UIManager::GetInstance().AddContent(UIType::Menu, msg);
		UIManager::GetInstance().AddContent(UIType::Menu, "공격할 대상을 선택하세요: ");
		break;
	}

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
	}
	SetMenu();
}

void BattleScene::Update(float delta_time)
{
    if (player_ui) {
        player_ui->Update(delta_time);
    }
    
    for (auto& ui : monster_uis) {
        if (ui) {
            ui->Update(delta_time);
        }
    }
    
    bool is_hit_stop = false;
    if (player_ui && player_ui->IsShake()) {
        is_hit_stop = true;
    }
    for (auto& ui : monster_uis) {
        if (ui && ui->IsShake()) {
            is_hit_stop = true;
        }
    }

    if (is_hit_stop) {
        return;
    }

    // 행동력 갱신은 Wait일때만
    if (current_state != BattleState::Wait) {
        return;
    }

    // 행동력 갱신
    battle_manager->UpdateGauge(delta_time, player_turn, monster_turn_idx);

    // UI 갱신
    if (player_ui) {
        player_ui->SetStatus(Character::GetInstance().GetHealth(),
            Character::GetInstance().GetMaxHealth(), battle_manager->GetPlayerGauge());
    }
    for (size_t i = 0; i < monsters.size(); ++i) {
        if (monsters[i] && !monsters[i]->IsDead()) {
            monster_uis[i]->SetStatus(monsters[i]->GetHealth(),
                monsters[i]->GetMaxHealth(), battle_manager->GetMonsterGauge(i));
        }
    }

    // 플레이어 턴이면
    if (player_turn) {
        current_state = BattleState::Act;
        SetMenu();
    }
    // -1이 아니면 idx에 해당하는 몬스터 턴
    else if (monster_turn_idx != -1) {
        battle_manager->SingleMonsterAttck(monster_turn_idx);
        player_ui->Shake(DURATION, INTENSITY);

        if (battle_manager->IsBattleOver()) {
            if (Character::GetInstance().IsDead()) {
                ChangeScene(SceneType::Title);
                return;
            }
        }
    }
}

void BattleScene::Render()
{
	// 배경
	BaseScene::Render();

	// 플레이어
	if (player_ui) {
		player_ui->Render();
	}

	// 몬스터
	for (size_t i = 0; i < monsters.size(); ++i) {
		if (!monsters[i]->IsDead()) {
			monster_uis[i]->Render();
		}
	}

}

void BattleScene::Release()
{
	BaseScene::Release();
	monsters.clear();
	monster_uis.clear();
	Character::GetInstance().ClearBuffs();
}

void BattleScene::SetSceneData(const std::string& data)
{
	if (!data.empty()) {
		is_boss_battle = (std::stoi(data) == 1);	// 1이면 보스전
	}
}


// private 함수
void BattleScene::ProcessActPhase(int key_code)
{
	switch (key_code) {
	case '1':
		current_state = BattleState::TargetEnemy;
		break;

	case '0':
	{
		if (!is_boss_battle) {
			UIManager::GetInstance().AddContent(UIType::Log, "[도망] 무사히 도망쳤습니다.");
			DungeonMapState::SetRandomBattleMap();
			ChangeScene(SceneType::Dungeon);
		}
		else {
			SetMenu();
			UIManager::GetInstance().AddContent(UIType::Menu, "도망칠 수 없습니다!!");
		}
		break;
	}

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

        // 몬스터 흔들기
        monster_uis[idx]->Shake(DURATION, INTENSITY);

        // 플레이어 행동력 초기화
        battle_manager->ResetPlayerGauge();

		if (monsters[idx]->IsDead()) {
			monster_uis[idx]->SetVisible(false);
		}

		// 전투 종료 판단
		if (battle_manager->IsBattleOver()) {
            if (is_boss_battle) {
                ChangeScene(SceneType::Ending);
            }
            else {
                battle_manager->DistributedReward();
                DungeonMapState::SetRandomBattleMap();
                ChangeScene(SceneType::Dungeon);
            }
		}
		else {
			current_state = BattleState::Wait;
		}
	}
}
