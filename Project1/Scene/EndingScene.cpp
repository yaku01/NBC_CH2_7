#include "EndingScene.h"
#include "UI/GameUI.h"
#include "UI/UIManager.h"
#include "Core/RenderSystem.h"


EndingScene::EndingScene() = default;
EndingScene::~EndingScene() = default;

void EndingScene::Init()
{
	int width = RenderSystem::GetInstance().GetScreenWidth();
	int height = RenderSystem::GetInstance().GetScreenHeight();

	int x = static_cast<int>(width * 0.2);
	int y = static_cast<int>(height * 0.1);
	int w = width - x * 2;
	int h = static_cast<int>(height * 0.6);

	ending_ui = std::make_unique<BorderUI>(x, y, w, h);
	ending_ui->AddContents("TEST");
	ending_ui->AddContents("TEST");
	ending_ui->AddContents("TEST");

	UIManager::GetInstance().SetAllVisible(false);
}

void EndingScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	Event ev{};
	ev.type = EventType::Quit;
	GameManager::GetInstance().PushEvent(ev);
}

void EndingScene::Update(float delta_time)
{
	current_time += delta_time;
	if (current_time >= INTERVAL) {
		current_time = 0.f;
		is_visible = !is_visible;
	}
}

void EndingScene::Render()
{
	ending_ui->Render();

	if (is_visible) {
		int w = RenderSystem::GetInstance().GetScreenWidth();
		int h = RenderSystem::GetInstance().GetScreenHeight();

		std::string text = "Press Any Key...";

		int x = (w - static_cast<int>(text.size())) / 2;
		int y = h - 5;
		RenderSystem::GetInstance().PrintText(x, y, text);
	}
}

bool EndingScene::IsExitable() const
{
	return false;
}
