#pragma once
#include "BaseScene.h"

class ExitPopUpScene : public BaseScene
{
public:
	ExitPopUpScene();

	void Init() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
};

