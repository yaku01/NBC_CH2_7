#pragma once
#include "BaseScene.h"
#include <memory>
#include <vector>
#include <string>

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

	// 통계 데이터 처리 변수
	std::vector<std::string> records;
	size_t current_idx = 0;
	float record_timer = 0.f; 
	bool is_finished = false;
	const float RECORD_INTERVAL = 1.f;

	// Press Any Key 깜빡임 연출
	bool is_visible = true;
	const float BLINK_INTERVAL = 0.5f;
	float blink_timer = 0.f;

    int GetVisualWidth(const std::string& str);
	void SetCenteredString(const std::string& text);
};

