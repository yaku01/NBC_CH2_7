#include "GameUI.h"
#include "Core/RenderSystem.h"
#include "Characters/Character.h"
#include "Monsters/Monster.h"
#include "Items/Item.h"
#include "Items/Consumable/ConsumableItem.h"
#include "Core/ItemDataBase.h"


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

void BorderUI::ClearBackGround()
{
    std::string blank(width, ' ');
    for (int i = 0; i < height; ++i) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, blank);
    }
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

    std::string hp_text = "Hp : " + std::to_string(player.GetHealth()) + " / " + std::to_string(player.GetMaxHealth());
    std::string atk_text = "Atk : " + std::to_string(player.GetAttack());
    if (player.GetBonusAttack() > 0) {
        atk_text += (" + " + std::to_string(player.GetBonusAttack()));
    }
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



ItemListUI::ItemListUI(int x, int y, int w, int h) : BorderUI(x, y, w, h)
{
}

void ItemListUI::NextPage(int total_items)
{
    int max_page = std::max(1, (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);

    if (current_page < max_page - 1) {
        ++current_page;
    }
}

void ItemListUI::PrevPage()
{
    if (current_page > 0) {
        --current_page;
    }
}

int ItemListUI::GetCurrentPage() const
{
    return current_page;
}

int ItemListUI::GetItemsPerPage() const
{
    return ITEMS_PER_PAGE;
}

void ItemListUI::RenderTitle(const std::string& title)
{
    int title_x = start_x + (width - static_cast<int>(title.length())) / 2;
    RenderSystem::GetInstance().PrintText(title_x, start_y + 1, title);
}

void ItemListUI::RenderPage(int total_items)
{
    int max_page = std::max(1, (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);

    // 아이템 사용으로 페이지 감소할 때 확인
    if (current_page >= max_page) {
        current_page = std::max(0, max_page - 1);
    }

    //  -- 페이지 표시 --
    int page_y = start_y + height - 2;
    RenderSystem::GetInstance().PrintText(start_x + 2, page_y, "[Q]");
    RenderSystem::GetInstance().PrintText(start_x + width - 5, page_y, "[E]");

    std::string page_text = "[" + std::to_string(current_page + 1) + " / " +
        std::to_string(max_page) + "]";
    int page_x = start_x + (width - static_cast<int>(page_text.length())) / 2;
    RenderSystem::GetInstance().PrintText(page_x, page_y, page_text);
}

int ItemListUI::GetStartIndex() const
{
    return current_page * ITEMS_PER_PAGE;
}

int ItemListUI::GetEndIndex(int total_items) const
{
    return std::min(GetStartIndex() + ITEMS_PER_PAGE, total_items);
}



InventoryUI::InventoryUI(int x, int y, int w, int h) : ItemListUI(x, y, w, h)
{
}

void InventoryUI::Render()
{
    BorderUI::Render();

    const auto& inventory = Character::GetInstance().GetInventory();

    int total_items = static_cast<int>(inventory.size());

    // 타이틀 출력
    std::string title = (is_active) ? "[ *** Inventory *** ]" : "Inventory";
    RenderTitle(title);
    
    // 아이템 출력
    int text_y = start_y + 3;
    if (total_items == 0) {
        RenderSystem::GetInstance().PrintText(start_x + 2, text_y, "인벤토리가 비어있습니다.");
    }
    else {
        int start_idx = GetStartIndex();
        int end_idx = GetEndIndex(total_items);

        for (int i = start_idx; i < end_idx; ++i) {
            IItem* item = inventory[i].get();
            if (!item){
                continue;
            }

            std::string stack_text = (item->GetType() == ItemType::Consumable) ?
                " x" + std::to_string(static_cast<ConsumableItem*>(item)->GetCount()) :
                "";
            std::string item_text = std::to_string(i - start_idx + 1) + ". " +
                std::string(item->GetName()) + stack_text;

            RenderSystem::GetInstance().PrintText(start_x + 2, text_y++, item_text);
        }
    }
    
    // 페이지 출력
    RenderPage(total_items);
}

void InventoryUI::ToggleActive()
{
    is_active = !is_active;
}

bool InventoryUI::IsActive() const
{
    return is_active;
}



ShopUI::ShopUI(int x, int y, int w, int h) : ItemListUI(x, y, w, h)
{
}

void ShopUI::Render()
{
    ClearBackGround();
    BorderUI::Render();

    const auto& inventory = Character::GetInstance().GetInventory();

    // 구매 - 상점리스트 / 판매 - 인벤토리
    int total_items = (is_buy_mode && shop_items) ?
        static_cast<int>(shop_items->size()) :
        static_cast<int>(inventory.size());

    // 타이틀 출력
    std::string title = (is_buy_mode) ? "- Shop (Buy) -" : "- Shop (Sell) -";
    RenderTitle(title);

    // 아이템 출력
    int text_y = start_y + 3;
    if (total_items == 0) {
        RenderSystem::GetInstance().PrintText(start_x + 2, text_y, "목록이 비어있습니다.");
    }
    else {
        int start_idx = GetStartIndex();
        int end_idx = GetEndIndex(total_items);
        
        for (int i = start_idx; i < end_idx; ++i) {
            std::string item_text = std::to_string(i - start_idx + 1) + ". ";
            std::string gold_text;

            if (is_buy_mode) {
                ItemID id = (*shop_items)[i];
                const ItemData& data = ItemDataBase::GetData(id);
                item_text += data.name;
                gold_text = std::to_string(data.price) + " Gold";
            }
            else {
                IItem* item = inventory[i].get();
                if (!item) {
                    continue;
                }

                // 판매는 원가의 60퍼 가격으로 책정
                const ItemData& data = ItemDataBase::GetData(item->GetID());
                item_text += data.name;
                gold_text = std::to_string(ItemDataBase::GetSellPrice(item->GetID())) + " Gold";
            }

            // 좌우 여백 2칸, 텍스트 제외하고 전부 공백 개수
            int black_count = width - 4 - static_cast<int>(item_text.length() + gold_text.length());
            if (black_count < 1) {
                black_count = 1;
            }

            std::string text = item_text + std::string(black_count, ' ') + gold_text;
            RenderSystem::GetInstance().PrintText(start_x + 2, text_y++, text);
        }
    }

    // 페이지 출력
    RenderPage(total_items);
}

void ShopUI::SetMode(bool is_buy_mode, const std::vector<ItemID>* item_ids)
{
    this->is_buy_mode = is_buy_mode;
    shop_items = item_ids;
    current_page = 0;
}



ItemConfirmUI::ItemConfirmUI(int x, int y, int w, int h)
    : BorderUI(x, y, w, h), action_text("")
{
}

void ItemConfirmUI::Render()
{
    if (target == ItemID::None) {
        return;
    }

    ClearBackGround();
    BorderUI::Render();
    
    const ItemData& data = ItemDataBase::GetData(target);

    // 질문 출력
    int text_y = start_y + 1;
    std::string question = data.name + "을(를) " + action_text;
    int text_x = start_x + (width - static_cast<int>(question.length())) / 2;
    RenderSystem::GetInstance().PrintText(text_x, text_y++, question);

    // 설명 출력
    std::string desc = data.desc;
    text_x = start_x + (width - static_cast<int>(desc.length())) / 2;
    RenderSystem::GetInstance().PrintText(text_x, text_y++, desc);
    ++text_y;
    ++text_y;

    // 선택지 출력
    std::string option = "[Y] YES  [N] NO";
    text_x = start_x + (width - static_cast<int>(option.length())) / 2;
    RenderSystem::GetInstance().PrintText(text_x, text_y, option);
}

void ItemConfirmUI::SetTarget(ItemID id)
{
    target = id;
}

void ItemConfirmUI::SetActionText(const std::string& action)
{
    action_text = action;
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



CharacterUI::CharacterUI(int x, int y) : AsciiUI(x, y), target(nullptr)
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

   

MonsterUI::MonsterUI(int x, int y) : AsciiUI(x, y), target(nullptr)
{
}

void MonsterUI::Render()
{
    AsciiUI::Render();

    // 이름 + 체력 출력
    if (target) {
        int info_y = start_y + static_cast<int>(contents.size()) + 1;

        RenderSystem::GetInstance().PrintText(start_x, info_y++, target->GetName());

        std::string hp_info = "HP: " + std::to_string(target->GetHealth()) +
            " / " + std::to_string(target->GetMaxHealth());
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



UpdateUI::UpdateUI(int x, int y, int w, int h, float max_time) : BaseUI(x, y, w, h), time(0.f), max_time(max_time)
{
}

void UpdateUI::Update(float delta_time)
{
    time += delta_time;
    if (time >= max_time) {
        time = max_time;
    }
}



WipeUI::WipeUI(int x, int y, int w, int h, float max_time) : UpdateUI(x, y, w, h, max_time)
{
}

void WipeUI::Render()
{
    float progress = time / max_time;   // 0.0 ~ 1.0 으로 변환
    int length = static_cast<int>(width * progress);

    // 홀수 줄 왼->오  >>>>
    std::string odd_line = std::string(length, '>');
    for (int i = 1; i < height; i += 2) {
        RenderSystem::GetInstance().PrintText(start_x, start_y + i, odd_line);
    }

    // 짝수 줄 오->왼  <<<<
    std::string even_line = std::string(length, '<');
    for (int i = 0; i < height; i += 2) {
        RenderSystem::GetInstance().PrintText(width - length, start_y + i, even_line);
    }
}



NoiseUI::NoiseUI(int x, int y, int w, int h, float max_time) : UpdateUI(x, y, w, h, max_time)
{
    // (A + B - 1) / B  -> 올림처리
    grid_cols = (width + block_w - 1) / block_w;
    grid_rows = (height + block_h - 1) / block_h;
    total_blocks = grid_cols * grid_rows;

    is_filled.assign(total_blocks, false);
    indices.reserve(total_blocks);

    for (int i = 0; i < total_blocks; ++i) {
        indices.push_back(i);
    }

    // 무작위로 섞기
    RandomUtil::Shuffle(indices);
}

void NoiseUI::Update(float delta_time)
{
    UpdateUI::Update(delta_time);

    float progress = time / max_time;   // 0.0 ~ 1.0 으로 변환

    // 채워야 하는 개수
    int target_count = static_cast<int>(total_blocks * progress);

    // 현재 채운 개수
    int current_count = total_blocks - static_cast<int>(indices.size());

    while (current_count < target_count && !indices.empty()) {
        int idx = indices.back();
        indices.pop_back();

        is_filled[idx] = true;
        ++current_count;
    }
}

void NoiseUI::Render()
{
    for (int i = 0; i < total_blocks; ++i) {
        if (!is_filled[i]) {
            continue;
        }

        // 1차원을 2차원으로 변환
        // 너비로 나머지 연산을 하면 열, 나누기를 하면 행
        int col = i % grid_cols;
        int row = i / grid_cols;

        // 시작 좌표
        int dx = start_x + (col * block_w);
        int dy = start_y + (row * block_h);
        
        // UI 영역 끝부분 넘어가지 않게 사이즈 조절
        int w = std::min(block_w, width - (col * block_w));
        int h = std::min(block_h, height - (row * block_h));

        std::string block_text(w, '#');

        for (int cy = 0; cy < h; ++cy) {
            RenderSystem::GetInstance().PrintText(dx, dy + cy, block_text);
        }
    }
}
