#pragma once
#include "Scene/BaseScene.h"
#include "UI/GameUI.h"
#include <memory>
#include <vector>


class BattleManager;
class Monster;

enum class BattleState {
	Act,
	TargetEnemy,
	UseItem
};

class BattleScene : public BaseScene
{
public:
	BattleScene();
	~BattleScene();

	void Init() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	void Release() override;

private:
	BattleManager* battle_manager = nullptr;
	std::vector<std::unique_ptr<Monster>> monsters;
	BattleState current_state = BattleState::Act;
	std::unique_ptr<CharacterUI> player_ui;
	std::vector<std::unique_ptr<MonsterUI>> monster_uis;


	void ProcessActPhase(int key_code);
	void ProcessTargetPhase(int key_code);
	void ProcessItemPhase(int key_code);
};

