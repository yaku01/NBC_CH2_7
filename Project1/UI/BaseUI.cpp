#include "BaseUI.h"
#include "Core/ResourceManager.h"

BaseUI::BaseUI(int x, int y, int w, int h) :
    start_x(x), start_y(y), width(w), height(h), is_visible(true)
{
    max_lines = std::max(1, height - 2);
}

BaseUI::BaseUI(int x, int y) : 
    start_x(x), start_y(y), width(0), height(0), is_visible(true), max_lines(0) 
{
}
 
void BaseUI::AddContents(std::string_view msg)
{
    contents.emplace_back(msg);
    if (static_cast<int>(contents.size()) > max_lines) {
        contents.pop_front(); // 꽉 차면 오래된 것 삭제
    }
}

void BaseUI::LoadAsciiArt(const std::string& path)
{
    auto res = ResourceManager::GetInstance().GetResource(path);
    if (res.has_value()) {
        contents = res->get();
    }
    else {
        contents.clear();
        contents.push_back("Resource Not Found");
    }
}

void BaseUI::Clear()
{
    contents.clear();
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

int BaseUI::GetWidth() const
{
    return width;
}

int BaseUI::GetHeight() const
{
    return height;
}
