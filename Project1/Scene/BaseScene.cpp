#include "BaseScene.h"
#include "Core/GameManager.h"

BaseScene::BaseScene()
{
	player = GameManager::GetInstance().GetPlayer();
}

void BaseScene::ChangeScene(SceneType scene)
{
	Event ev{};
	ev.type = EventType::ChangeScene;
	ev.next_scene = scene;

	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::PushScene(SceneType scene)
{
	Event ev{};
	ev.type = EventType::PushScene;
	ev.next_scene = scene;

	GameManager::GetInstance().PushEvent(ev);
}

void BaseScene::PopScene()
{
	Event ev{};
	ev.type = EventType::PopScene;

	GameManager::GetInstance().PushEvent(ev);
}

bool BaseScene::IsOpaque() const
{
	return is_opaque;
}
