#include "ExitPopUpScene.h"
#include "Core/GameManager.h"
#include "UI/UIManager.h"
#include "Core/RenderSystem.h"
#include "UI/GameUI.h"

ExitPopUpScene::ExitPopUpScene() : BaseScene()
{
	is_opaque = false;
}

void ExitPopUpScene::Init()
{
	// 콘솔 사이즈 구하기
	int w = RenderSystem::GetInstance().GetScreenWidth();
	int h = RenderSystem::GetInstance().GetScreenHeight();

	int x = static_cast<int>(w * 0.15);
	int y = static_cast<int>(h * 0.15);

	auto pop_up = std::make_unique<AsciiUI>(x, y);
	pop_up->LoadAsciiArt("Resource/ExitPopup.txt");
	scene_uis.push_back(std::move(pop_up));
}

void ExitPopUpScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	switch (e.key_code) {
	case 'y':
	case 'Y':
	{
		Event ev{};
		ev.type = EventType::Quit;
		GameManager::GetInstance().PushEvent(ev);
		break;
	}

	case 'n':
	case 'N':
	case 27:	//ESC
		PopScene();
		break;
	}
}

void ExitPopUpScene::Update(float delta_time)
{
}
