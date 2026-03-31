#include "EndingScene.h"
#include "UI/GameUI.h"
#include "UI/UIManager.h"
#include "Core/RenderSystem.h"
#include "Core/LogManager.h"


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

	SetCenteredString("================================");
	SetCenteredString("       [ 게 임 클 리 어 ]       ");
	SetCenteredString("================================");
	SetCenteredString("");
	SetCenteredString("< 플레이  기록 >");


	records = LogManager::GetInstance().GetStatsSummary();
	UIManager::GetInstance().SetAllVisible(false);
}

void EndingScene::ProcessEvent(const Event& e)
{
	if (e.type != EventType::KeyDown) {
		return;
	}

	// 로그 내용 출력중이면
	if (!is_finished) {
		is_finished = true;

		for (size_t i = current_idx; i < records.size(); ++i) {
			SetCenteredString(records[i]);
		}
		current_idx = records.size();
	}
	// 출력이 끝났다면
	else {
		Event ev{};
		ev.type = EventType::Quit;
		GameManager::GetInstance().PushEvent(ev);
	}
}

void EndingScene::Update(float delta_time)
{
	if (!is_finished) {
		record_timer += delta_time;
		if (record_timer >= RECORD_INTERVAL) {
			record_timer = 0.f;
			
			if (current_idx < records.size()) {
				SetCenteredString(records[current_idx]);
				++current_idx;
			}
			else {
				is_finished = true; 
			}
		}
	}
	else {
		blink_timer += delta_time;
		if (blink_timer >= BLINK_INTERVAL) {
			blink_timer = 0.f;
			is_visible = !is_visible;
		}
	}

}

void EndingScene::Render()
{
	ending_ui->Render();

	if (is_finished && is_visible) {
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


// private 함수
void EndingScene::SetCenteredString(const std::string& text)
{
	if (!ending_ui) {
		return;
	}

	int width = ending_ui->GetWidth();
	int blank_count = (width - static_cast<int>(text.length())) / 2 - 2;

	if (blank_count > 0) {
		ending_ui->AddContents(std::string(blank_count, ' ') + text);
	}
	else {
		ending_ui->AddContents(text);
	}
}
