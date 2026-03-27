#pragma once
#include "BaseScene.h"

class TownScene : public BaseScene
{
public:
	TownScene() = default;

	void Init() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Release() override;
};

