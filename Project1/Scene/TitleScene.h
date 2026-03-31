#pragma once
#include "BaseScene.h"
#include <string>

class TitleScene : public BaseScene
{
public:
	TitleScene() = default;

	void Init() override;
	void SetMenu() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;

private:
	std::string name;
};

