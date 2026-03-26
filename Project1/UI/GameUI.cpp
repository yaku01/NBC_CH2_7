#include "GameUI.h"
#include "Core/RenderSystem.h"

MessageUI::MessageUI(int x, int y, int w, int h) : BaseUI(x, y, w, h)
{
    top_border = "┌";
    bottom_border = "└";

    for (int i = 0; i < width - 2; ++i) {
        top_border += "─";
        bottom_border += "─";
    }

    top_border += "┐";
    bottom_border += "┘";
}

void MessageUI::Render()
{
    // 상단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y, top_border);

    // 세로선
    for (int i = 1; i < height - 1; ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, "│");
        RenderSystem::GetInstance().PrintText(start_x + width - 1, start_y + i, "│");
    }

    // 메세지 출력
    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1 + i,
            "[알림] " + messages[i]);
    }

    // 하단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y + height - 1, bottom_border);
}

LogUI::LogUI(int x, int y, int w, int h) : BaseUI(x, y, w, h)
{
    top_border = "┌";
    bottom_border = "└";

    for (int i = 0; i < width - 2; ++i) {
        top_border += "─";
        bottom_border += "─";
    }

    top_border += "┐";
    bottom_border += "┘";
}

void LogUI::Render()
{
    // 상단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y, top_border);

    // 세로선
    for (int i = 1; i < height - 1; ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, "│");
        RenderSystem::GetInstance().PrintText(start_x + width - 1, start_y + i, "│");
    }

    // 로그 구역 표시
    RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1, "[ 전투 / 행동 로그 ]");

    // 내용 출력
    for (int i = 0; i < messages.size(); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 2 + i,
            messages[i]);
    }

    // 하단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y + height - 1, bottom_border);
}

void LogUI::AddMessage(std::string_view msg)
{
    int length = width - 2;
    std::string_view line = msg;

    // 문자열 자르기 반복
    while (line.size() >= length) {
        BaseUI::AddMessage(line.substr(0, length));
        line = line.substr(length);
    }

    if (!line.empty()) {
        BaseUI::AddMessage(line);
    }
}
