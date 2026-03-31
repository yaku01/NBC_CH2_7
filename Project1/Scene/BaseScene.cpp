#include "BaseScene.h"
#include "Core/GameManager.h"
#include  "UI/BaseUI.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene() = default;

void BaseScene::Render()
{
	for (const auto& ui : scene_uis) {
		if (ui->IsVisible()) {
			ui->Render();
		}
	}
}

void BaseScene::Release()
{
	scene_uis.clear();
}

void BaseScene::ChangeScene(SceneType scene)
{
	Event ev{};
	ev.type = EventType::ChangeScene;
	ev.next_scene = scene;

	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::PushScene(SceneType scene, const std::string& data)
{
	Event ev{};
	ev.type = EventType::PushScene;
	ev.next_scene = scene;
	ev.scene_data = data;

	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::PopScene()
{
	Event ev{};
	ev.type = EventType::PopScene;

	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::ReplaceScene(SceneType scene, const std::string& data)
{
	Event ev{};
	ev.type = EventType::ReplaceScene;
	ev.next_scene = scene;
	ev.scene_data = data;

	GameManager::GetInstance().PushEvent(ev);
}

bool BaseScene::IsOpaque() const
{
	return is_opaque;
}
