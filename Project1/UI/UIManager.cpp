#include "UIManager.h"
#include "UI/GameUI.h"
#include "Core/RenderSystem.h"

UIManager::UIManager()
{
    // 콘솔 사이즈 구하기
    int w = RenderSystem::GetInstance().GetScreenWidth();
    int h = RenderSystem::GetInstance().GetScreenHeight();

    int msg_width = static_cast<int>(w * 0.7f);
    int msg_height = static_cast<int>(h * 0.2f);
    int msg_x = 0;
    int msg_y = h - msg_height;
    ui_list.push_back(std::make_unique<MessageUI>(msg_x, msg_y, msg_width, msg_height));

    int log_width = w - msg_width - 1;
    int log_height = h;
    int log_x = msg_width;
    int log_y = 0;
    ui_list.push_back(std::make_unique<LogUI>(log_x, log_y, log_width, log_height));

    // 킬보드 UI 추가
    int kill_width = static_cast<int>(w * 0.15f);
    int kill_height = static_cast<int>(h * 0.5f);
    int kill_x = msg_width - kill_width;
    int kill_y = 0;
    ui_list.push_back(std::make_unique<KillBoardUI>(kill_x, kill_y, kill_width, kill_height));
}

UIManager::~UIManager()
{
}

void UIManager::AddMessage(UIType type, std::string_view msg)
{
    size_t idx = static_cast<size_t>(type);

    if (idx < static_cast<size_t>(UIType::COUNT)) {
        ui_list[idx]->AddMessage(msg);
    }
}

void UIManager::ClearMessage(UIType type)
{
    size_t idx = static_cast<size_t>(type);

    if (idx < static_cast<size_t>(UIType::COUNT)) {
        ui_list[idx]->Clear();
    }
}

void UIManager::ClearAll(const std::vector<UIType>& ignores)
{
    for (size_t i = 0; i < static_cast<size_t>(UIType::COUNT); ++i) {
        UIType current_type = static_cast<UIType>(i);

        auto it = std::find(ignores.begin(), ignores.end(), current_type);
        if (it != ignores.end()) {
            continue;
        }

        ui_list[i]->Clear();
    }
}

void UIManager::Render()
{
    // 로그ui, 메세지ui 등 전역 ui 그리기
    for (const auto& ui : ui_list) {
        if (ui->IsVisible()) {
            ui->Render();
        }
    }
}

void UIManager::SetVisible(UIType type, bool value)
{
    size_t idx = static_cast<size_t>(type);
    if (idx < static_cast<size_t>(UIType::COUNT)) {
        ui_list[idx]->SetVisible(value);
    }
}

void UIManager::SetAllVisible(bool value)
{
    for (auto& ui : ui_list) {
        ui->SetVisible(value);
    }
}

void UIManager::OnMonsterKilled(const std::string& monster_name)    // 킬보드에 킬 추가
{
    static_cast<KillBoardUI*>(ui_list[2].get())->AddKill(monster_name);
}