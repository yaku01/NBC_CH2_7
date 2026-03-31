#pragma once
#include "BaseScene.h"
#include <memory>

class UpdateUI;

class EncounterScene : public BaseScene
{
public:
	EncounterScene();
	~EncounterScene();

	void Init() override;
	void ProcessEvent(const Event& e) override;
	void Update(float delta_time) override;
	void Render() override;
	void Release() override;
	void SetSceneData(const std::string& data) override;

private:
	float current_time = 0.f;
	float max_time = 0.f;
	std::unique_ptr<UpdateUI> ui;
	SceneType next_scene = SceneType::None;
};

