#include "EncounterScene.h"
#include "UI/GameUI.h"
#include "Core/GameManager.h"
#include "Core/RenderSystem.h"
#include <sstream>


EncounterScene::EncounterScene() = default;
EncounterScene::~EncounterScene() = default;

void EncounterScene::Init()
{
	is_opaque = false;

	int w = RenderSystem::GetInstance().GetScreenWidth();
	int h = RenderSystem::GetInstance().GetScreenHeight();

	ui = std::make_unique<NoiseUI>(0, 0, w, h, max_time);
}

void EncounterScene::ProcessEvent(const Event& e)
{
}

void EncounterScene::Update(float delta_time)
{
	current_time += delta_time;
	ui->Update(delta_time);

	if (current_time >= max_time) {
		ReplaceScene(next_scene);
	}
}

void EncounterScene::Render()
{
	ui->Render();
}

void EncounterScene::Release()
{
}

void EncounterScene::SetSceneData(const std::string& data)
{
	std::stringstream ss(data);
	int next{};
	ss >> next >> max_time;
	next_scene = static_cast<SceneType>(next);
}
