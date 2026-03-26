#pragma once
#include "Scene/BaseScene.h"

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
	BattleScene() = default;

	void Init() override;
	void SetUI() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	void Release() override;

private:
	BattleManager* battle_manager = nullptr;
	std::vector<Monster*> monsters;
	BattleState current_state = BattleState::Act;

	void ProcessActPhase(int key_code);
	void ProcessTargetPhase(int key_code);
	void ProcessItemPhase(int key_code);
};

