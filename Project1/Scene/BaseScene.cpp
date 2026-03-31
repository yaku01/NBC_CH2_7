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

bool BaseScene::IsExitable() const
{
	return true;
}
