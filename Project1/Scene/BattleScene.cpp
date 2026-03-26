#include "BattleScene.h"
#include "Core/GameManager.h"
#include "GamePlay/Battle/BattleManager.h"
#include "UI/UIManager.h"
#include "Monster.h"

void BattleScene::Init()
{
	battle_manager = GameManager::GetInstance().GetBattleManager();

	int monster_count =

	SetUI();
	SetMenu();
}

void BattleScene::SetUI()
{
}

void BattleScene::SetMenu()
{

}

void BattleScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}


}

void BattleScene::Update(float delta_time)
{
}

void BattleScene::Render()
{
}

void BattleScene::Release()
{
}
