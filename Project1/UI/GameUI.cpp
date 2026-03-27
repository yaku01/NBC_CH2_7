#include "GameUI.h"
#include "Core/RenderSystem.h"
#include "Characters/Character.h"
#include "Monster.h"
#include "Items/Item.h"
#include <fstream>


BorderUI::BorderUI(int x, int y, int w, int h) : BaseUI(x, y, w, h)
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

void BorderUI::Render()
{
    // 상단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y, top_border);

    // 세로선
    for (int i = 1; i < height - 1; ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, "│");
        RenderSystem::GetInstance().PrintText(start_x + width - 1, start_y + i, "│");
    }

    // 메세지 출력
    for (int i = 0; i < static_cast<int>(contents.size()); ++i) {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1 + i, contents[i]);
    }

    // 하단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y + height - 1, bottom_border);
}



LogUI::LogUI(int x, int y, int w, int h) : BorderUI(x, y, w, h)
{
}

void LogUI::AddContents(std::string_view msg)
{
    int length = width - 2;
    std::string_view line = msg;

    // 문자열 자르기 반복
    while (line.size() >= length) {
        BaseUI::AddContents(line.substr(0, length));
        line = line.substr(length);
    }

    if (!line.empty()) {
        BaseUI::AddContents(line);
    }
}



CharacterInfoUI::CharacterInfoUI(int x, int y, int w, int h) : BorderUI(x, y, w, h)
{
}

void CharacterInfoUI::Render()
{
    BorderUI::Render();

    const Character& player = Character::GetInstance();

    std::string level_text = "Level : " + std::to_string(player.GetLevel());
    std::string exp_text = "Exp : " + std::to_string(player.GetExperience()) + " / " + std::to_string(100);

    // GetStatus()가 Status 객체를 반환하고 내부에서 operator[]를 오버로딩했으므로 바로 사용 가능합니다.
    std::string hp_text = "Hp : " + std::to_string(player.GetHealth()) + " / " + std::to_string(player.GetMaxHealth());
    std::string atk_text = "Atk : " + std::to_string(player.GetAttack());
    std::string gold_text = "Gold : " + std::to_string(player.GetGold());

    int text_x = start_x + 2;
    int text_y = start_y + 1;

    RenderSystem::GetInstance().PrintText(text_x, text_y++, player.GetName());
    RenderSystem::GetInstance().PrintText(text_x, text_y++, level_text);
    RenderSystem::GetInstance().PrintText(text_x, text_y++, exp_text);
    ++text_y;

    RenderSystem::GetInstance().PrintText(text_x, text_y++, hp_text);
    RenderSystem::GetInstance().PrintText(text_x, text_y++, atk_text);
    RenderSystem::GetInstance().PrintText(text_x, text_y++, gold_text);
}



ItemUI::ItemUI(int x, int y, int w, int h) : BorderUI(x, y, w, h)
{
}

void ItemUI::Render()
{
    BorderUI::Render();

    const Character& player = Character::GetInstance();
    const auto& inventory = player.GetInventory();

    int total_items = static_cast<int>(inventory.size());
    int max_page = std::max(1, (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);

    // 아이템 사용해서 max_page가 줄어들면
    if (current_page >= max_page) {
        current_page = max_page - 1;
    }

    // 상단 타이틀 출력
    std::string title = "Inventory";
    int title_x = start_x + (width - static_cast<int>(title.length())) / 2;
    int text_y = start_y + 1;
    RenderSystem::GetInstance().PrintText(title_x, text_y++, title);
    ++text_y;
    
    
    // 아이템 출력
    if (total_items == 0) {
        RenderSystem::GetInstance().PrintText(start_x + 2, text_y, "인벤토리가 비어있습니다.");
    }
    else {
        int start_idx = current_page * ITEMS_PER_PAGE;
        int end_idx = std::min(start_idx + ITEMS_PER_PAGE, total_items);

        for (int i = start_idx; i < end_idx; ++i) {
            IItem* item = inventory[i].get();
            if (!item){
                continue;
            }

            std::string item_text = std::to_string(i - start_idx + 1) + ". " +
                std::string(item->GetName());

            RenderSystem::GetInstance().PrintText(start_x + 2, text_y++, item_text);
        }
    }


    //  -- 페이지 표시 --
    int page_y = start_y + height - 2;

    // 왼쪽 [Q], 오른쪽 [E]
    RenderSystem::GetInstance().PrintText(start_x + 2, page_y, "[Q]");
    RenderSystem::GetInstance().PrintText(start_x + width - 5, page_y, "[E]");

    // 중앙 페이지 표시
    std::string page_text = "[" + std::to_string(current_page + 1) + " / " +
        std::to_string(max_page) + "]";
    int page_x = start_x + (width - static_cast<int>(page_text.length())) / 2;
    RenderSystem::GetInstance().PrintText(page_x, page_y, page_text);

}

void ItemUI::NextPage()
{
    const Character& player = Character::GetInstance();
    int total_items = static_cast<int>(player.GetInventory().size());
    int max_page = std::max(1, (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);

    if (current_page < max_page - 1) {
        ++current_page;
    }
}

void ItemUI::PrevPage()
{
    if (current_page > 0) {
        --current_page;
    }
}



AsciiUI::AsciiUI(int x, int y) : BaseUI(x, y)
{
}

void AsciiUI::Render()
{
    for (int i = 0; i < static_cast<int>(contents.size()); ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, contents[i]);
    }
}



CharacterUI::CharacterUI(int x, int y) : AsciiUI(x, y)
{
}

void CharacterUI::Render()
{
    AsciiUI::Render();

    // 체력 출력
    if (target) {
        std::string hp_info = "HP: " + std::to_string(target->GetHealth()) +
            " / " + std::to_string(target->GetMaxHealth());

        int info_y = start_y + static_cast<int>(contents.size()) + 1;
        RenderSystem::GetInstance().PrintText(start_x, info_y, hp_info);
    }
}

void CharacterUI::SetTarget(const Character* target)
{
    this->target = target;
}

   

MonsterUI::MonsterUI(int x, int y) : AsciiUI(x, y)
{
}

void MonsterUI::Render()
{
    AsciiUI::Render();

    // 체력 출력
    if (target) {
        std::string hp_info = "HP: " + std::to_string(target->GetHealth()) +
            " / " + std::to_string(target->GetMaxHealth());

        int info_y = start_y + static_cast<int>(contents.size()) + 1;
        RenderSystem::GetInstance().PrintText(start_x, info_y, hp_info);
    }
}

void MonsterUI::SetTarget(const Monster* target)
{
    this->target = target;
}

// 킬보드 UI 초기화
KillBoardUI::KillBoardUI(int x, int y, int w, int h) : BaseUI(x, y, w, h)
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

// 킬보드 UI 그리기
void KillBoardUI::Render()
{
    // 상단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y, top_border);

    // 세로선
    for (int i = 1; i < height - 1; ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, "│");
        RenderSystem::GetInstance().PrintText(start_x + width - 1, start_y + i, "│");
    }

    // 킬보드 제목
    RenderSystem::GetInstance().PrintText(start_x + 2, start_y + 1, "[ 킬 보드 ]");

    // 킬카운트 출력
    int line = 2;
    for (const auto& k : kill_count_)
    {
        RenderSystem::GetInstance().PrintText(start_x + 2, start_y + line,
            k.first + " x" + std::to_string(k.second));
        line++;
    }

    // 하단 경계선
    RenderSystem::GetInstance().PrintText(start_x, start_y + height - 1, bottom_border);
}

void KillBoardUI::AddKill(const std::string& monster_name)   // 킬보드에 킬 추가
{
    ++kill_count_[monster_name];
}
