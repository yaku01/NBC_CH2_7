#pragma once
#include "BaseScene.h"

class DungeonScene : public BaseScene
{
public:
	DungeonScene() = default;

	void Init() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Release() override;
};

