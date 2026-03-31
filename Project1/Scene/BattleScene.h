#pragma once
#include "Scene/BaseScene.h"

#include <memory>
#include <vector>

class BattleUnitUI;
class BattleManager;
class Monster; 

enum class BattleState {
    Wait,
	Act,
	TargetEnemy
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
	void SetSceneData(const std::string& data) override;

private:
	BattleManager* battle_manager = nullptr;
	std::vector<std::unique_ptr<Monster>> monsters;
	BattleState current_state = BattleState::Act;
	std::unique_ptr<BattleUnitUI> player_ui;
	std::vector<std::unique_ptr<BattleUnitUI>> monster_uis;
	bool is_boss_battle = false;
    bool player_turn = false;
    int monster_turn_idx = -1;

	void ProcessActPhase(int key_code);
	void ProcessTargetPhase(int key_code);
};

