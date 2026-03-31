#pragma once
#include "BaseScene.h"
#include <memory>

class BorderUI;

class EndingScene : public BaseScene
{
public:
	EndingScene();
	~EndingScene();

	void Init() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	bool IsExitable() const override;

private:
	std::unique_ptr<BorderUI> ending_ui;
	bool is_visible = true;
	const float INTERVAL = 0.5f;
	float current_time = 0.f;
};

