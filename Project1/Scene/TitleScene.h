#pragma once
#include "BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() = default;

	void Init() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
};

