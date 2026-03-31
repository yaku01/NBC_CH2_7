#include "UIManager.h"
#include "UI/GameUI.h"
#include "Core/RenderSystem.h"
#include "Characters/Character.h"

UIManager::UIManager()
{
    // 콘솔 사이즈 구하기
    int w = RenderSystem::GetInstance().GetScreenWidth();
    int h = RenderSystem::GetInstance().GetScreenHeight();

    // 메뉴 좌하단 시작 길이 0.7, 높이 0.2
    int menu_width = static_cast<int>(w * 0.7f);
    int menu_height = static_cast<int>(h * 0.2f);
    int menu_x = 0;
    int menu_y = h - menu_height;
    uis.push_back(std::make_unique<BorderUI>(menu_x, menu_y, menu_width, menu_height));

    // 우측 영역 변수
    int right_area_width = w - menu_width - 1;
    int right_area_x = menu_width;


    // 인포
    int info_width = right_area_width / 2;
    int info_height = static_cast<int>(h * 0.2f);
    int info_y = 0;
    uis.push_back(std::make_unique<CharacterInfoUI>(right_area_x, info_y, right_area_width, info_height));
    

    // 로그  높이 0.45
    int log_height = static_cast<int>(h * 0.45f);
    int log_y = h - log_height;
    uis.push_back(std::make_unique<LogUI>(right_area_x, log_y, right_area_width, log_height));


    // 아이템
    int item_height = h - info_height - log_height;
    uis.push_back(std::make_unique<InventoryUI>(right_area_x, info_height, right_area_width, item_height));

    // 킬보드 UI 추가
    int kill_width = static_cast<int>(w * 0.15f);
    int kill_height = static_cast<int>(h * 0.5f);
    int kill_x = menu_width - kill_width;
    int kill_y = 0;
    uis.push_back(std::make_unique<KillBoardUI>(kill_x, kill_y, kill_width, kill_height));
}

UIManager::~UIManager()
{
} 

void UIManager::AddContent(UIType type, std::string_view msg)
{
    size_t idx = static_cast<size_t>(type);

    if (idx < static_cast<size_t>(UIType::COUNT)) {
        uis[idx]->AddContents(msg);
    }

    // 카운트 추가 - 게임 로그 카운트 체크
    if (type == UIType::Log) {
        std::string s(msg);
        if (s.find("[공격]") != std::string::npos) count_attack_++;
        else if (s.find("[피격]") != std::string::npos) count_damage_++;
        else if (s.find("[조우]") != std::string::npos) count_encounter_++;
        else if (s.find("[이동]") != std::string::npos) count_move_++;
        else if (s.find("[휴식]") != std::string::npos) count_rest_++;
        else if (s.find("[보상]") != std::string::npos) count_reward_++;
        else if (s.find("[도망]") != std::string::npos) count_escape_++;
        else if (s.find("[사망]") != std::string::npos) count_death_++;
        else if (s.find("[사용]") != std::string::npos) count_use_++;
    }

}

void UIManager::ClearContent(UIType type)
{
    size_t idx = static_cast<size_t>(type);

    if (idx < static_cast<size_t>(UIType::COUNT)) {
        uis[idx]->Clear();
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

        uis[i]->Clear();
    }
}

void UIManager::Render()
{
    // 로그ui, 메세지ui 등 전역 ui 그리기
    for (const auto& ui : uis) {
        if (ui->IsVisible()) {
            ui->Render();
        }
    }
}

void UIManager::SetVisible(UIType type, bool value)
{
    size_t idx = static_cast<size_t>(type);
    if (idx < static_cast<size_t>(UIType::COUNT)) {
        uis[idx]->SetVisible(value);
    }
}

void UIManager::SetAllVisible(bool value)
{
    for (auto& ui : uis) {
        ui->SetVisible(value);
    }
}

void UIManager::NextPageItemUI()
{
    auto* item_ui = static_cast<InventoryUI*>(uis[static_cast<int>(UIType::Inventory)].get());
    int total_items = static_cast<int>(Character::GetInstance().GetInventory().size());
    item_ui->NextPage(total_items);
}

void UIManager::PrevPageItemUI()
{
    auto* item_ui = static_cast<InventoryUI*>(uis[static_cast<int>(UIType::Inventory)].get());
    item_ui->PrevPage();
}

void UIManager::OnMonsterKilled(const std::string& monster_name)    // 킬보드에 킬 추가
{
    static_cast<KillBoardUI*>(uis[static_cast<int>(UIType::KillLog)].get())->AddKill(monster_name);
}

void UIManager::ToggleItemUI()
{
    auto* item_ui = static_cast<InventoryUI*>(uis[static_cast<int>(UIType::Inventory)].get());
    item_ui->ToggleActive();
}

int UIManager::GetItemUICurrentPage() const
{
    auto* item_ui = static_cast<InventoryUI*>(uis[static_cast<int>(UIType::Inventory)].get());
    return item_ui->GetCurrentPage();
}

int UIManager::GetItemUIItemsPerPage() const
{
    auto* item_ui = static_cast<InventoryUI*>(uis[static_cast<int>(UIType::Inventory)].get());
    return item_ui->GetItemsPerPage();
}

void UIManager::SaveLogToFile(const std::string& filename) //로그 세이브 구현
{
    std::ofstream file(filename);

    int total_kills = 0;
    auto* kill_ui = static_cast<KillBoardUI*>(uis[static_cast<int>(UIType::KillLog)].get());
    for (const auto& k : kill_ui->GetKillCount())
        total_kills += k.second;

    file << "\n=== 통계 ===\n";
    file << "[공격] 횟수: " << count_attack_ << "\n";
    file << "[피격] 횟수: " << count_damage_ << "\n";
    file << "[조우] 횟수: " << count_encounter_ << "\n";
    file << "[이동] 횟수: " << count_move_ << "\n";
    file << "[휴식] 횟수: " << count_rest_ << "\n";
    file << "[보상] 획득: " << count_reward_ << "\n";
    file << "[도망] 횟수: " << count_escape_ << "\n";
    file << "[사망] 횟수: " << count_death_ << "\n";
    file << "[사용] 횟수: " << count_use_ << "\n";
    file << "[처치] 횟수: " << total_kills << "\n"; //[처치] 횟수는 멤버변수 대신 킬보드에서 직접 합산하여 저장

    // 킬보드 저장
    file << "\n=== 킬 보드 ===\n";
    for (const auto& k : kill_ui->GetKillCount())
        file << k.first << " x" << k.second << "\n";

    // 전투 로그 저장
    file << "\n=== 전투 로그 ===\n";
    auto* log_ui = uis[static_cast<int>(UIType::Log)].get();
    for (const auto& line : log_ui->GetAllContents())
        file << line << "\n";

    file.close();
}

void UIManager::LoadLogFromFile(const std::string& filename) //로그 로드 구현
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    bool is_log_section = false;  // 전투 로그 섹션 체크용

    while (std::getline(file, line))
    {
        if (line.find("[공격] 횟수: ") != std::string::npos)
            count_attack_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[피격] 횟수: ") != std::string::npos)
            count_damage_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[조우] 횟수: ") != std::string::npos)
            count_encounter_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[이동] 횟수: ") != std::string::npos)
            count_move_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[휴식] 횟수: ") != std::string::npos)
            count_rest_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[보상] 획득: ") != std::string::npos)
            count_reward_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[도망] 횟수: ") != std::string::npos)
            count_escape_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[사망] 횟수: ") != std::string::npos)
            count_death_ = std::stoi(line.substr(line.find(": ") + 2));
        else if (line.find("[사용] 횟수: ") != std::string::npos)
            count_use_ = std::stoi(line.substr(line.find(": ") + 2));
        
        // 킬보드 읽기
        else if (line.find("=== 킬 보드 ===") != std::string::npos)
            is_log_section = false;
        else if (line.find("=== 전투 로그 ===") != std::string::npos)
            is_log_section = true;
        else if (line.find(" x") != std::string::npos && !is_log_section)
        {
            size_t pos = line.find(" x");
            std::string name = line.substr(0, pos);
            int count = std::stoi(line.substr(pos + 2));
            auto* kill_ui = static_cast<KillBoardUI*>(
                uis[static_cast<int>(UIType::KillLog)].get());
            for (int i = 0; i < count; i++)
                kill_ui->AddKill(name);
        }

        // 전투 로그 읽기
        else if (is_log_section && !line.empty())
        {
            uis[static_cast<int>(UIType::Log)].get()->AddContents(line);
        }
    }
    file.close();
}

void UIManager::ResetStats() //로그 통계 및 기록 전체 초기화
{
    //통계 카운터 초기화
    count_attack_ = 0;
    count_damage_ = 0;
    count_encounter_ = 0;
    count_move_ = 0;
    count_rest_ = 0;
    count_reward_ = 0;
    count_escape_ = 0;
    count_death_ = 0;
    count_use_ = 0;

    // 킬보드 초기화
    static_cast<KillBoardUI*>(
        uis[static_cast<int>(UIType::KillLog)].get())->ClearKills();

    // 화면에 보이는 전투 로그 초기화
    ClearContent(UIType::Log);
    
    // 전체 전투 로그(파일 저장용) 초기화
    uis[static_cast<int>(UIType::Log)].get()->ClearAllContents();
}
