#include "BaseUI.h"

BaseUI::BaseUI(int x, int y, int w, int h) :
    start_x(x), start_y(y), width(w), height(h), is_visible(true)
{
    max_lines = std::max(1, height - 2);
}

void BaseUI::AddMessage(std::string_view msg)
{
    messages.emplace_back(msg);
    if (static_cast<int>(messages.size()) > max_lines) {
        messages.pop_front(); // 꽉 차면 오래된 것 삭제
    }
}

void BaseUI::Clear()
{
    messages.clear();
}

void BaseUI::SetVisible(bool valid)
{
    is_visible = valid;
}

void BaseUI::ToggleVisible()
{
    is_visible = !is_visible;
}

bool BaseUI::IsVisible() const
{
    return is_visible;
}
