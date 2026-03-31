#include "LogManager.h"
#include "UI/UIManager.h"
#include <fstream>
#include <sstream>

void LogManager::AddLog(std::string_view msg)
{
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

    all_logs_.push_back(s);

    UIManager::GetInstance().AddContent(UIType::Log, msg);
}

void LogManager::AddKill(const std::string& monster_name)
{
    ++kill_counts_[monster_name];
}

void LogManager::SaveLogToFile(const std::string& filename, const std::string& player_name)
{
    // 1. 기존 파일 읽기
    std::ifstream infile(filename);
    std::stringstream buffer;
    std::string line;
    bool skip = false;

    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            if (line == "[LOG_DATA]") {
                std::string name_line;
                std::getline(infile, name_line);

                if (name_line == player_name) {
                    skip = true; // 현재 플레이어의 예전 로그 블록은 덮어쓸 것이므로 무시(Skip)
                    continue;
                }
                else {
                    buffer << "[LOG_DATA]\n" << name_line << "\n";
                }
            }
            else if (line == "[END_LOG]") {
                if (!skip) {
                    buffer << line << "\n";   
                }
                else {
                    skip = false; // 스킵 후 다시 정상 읽기
                }
            }
            else if (!skip) {
                buffer << line << "\n";
            }
        }
        infile.close();
    }


    // 파일 덮어쓰기
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << buffer.str(); 

    file << "[LOG_DATA]\n";
    file << player_name << "\n";

    int total_kills = 0;
    for (const auto& k : kill_counts_)
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
    for (const auto& k : kill_counts_)
        file << k.first << " x" << k.second << "\n";

    // 전투 로그 저장
    file << "\n=== 전투 로그 ===\n";
    for (const auto& line : all_logs_)
        file << line << "\n";

    file << "[END_LOG]\n"; // 블록 끝을 알리는 태그
    file.close();
}

void LogManager::LoadLogFromFile(const std::string& filename, const std::string& player_name)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    ResetStats();

    std::string line;
    bool is_target_player = false;
    bool is_log_section = false;  // 전투 로그 섹션 체크용

    while (std::getline(file, line))
    {
        // 로그 시작점이라면 플레이어 확인
        if (line == "[LOG_DATA]") {
            std::string name;
            std::getline(file, name);
            if (name == player_name) {
                is_target_player = true; // 찾던 플레이어의 블록 발견!
            }
            else {
                is_target_player = false;
            }
            continue;
        }

        // 로그 끝점이라면 다 읽은건지 확인
        if (line == "[END_LOG]") {
            if (is_target_player) {
                break; // 목표 플레이어의 로드가 끝났으므로 루프 탈출
            }
            continue;
        }

        // 기록된 플레이어가 아니라면 아래 파싱 무효
        if (!is_target_player) {
            continue;
        }

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
            
            kill_counts_[name] = count;
        }

        // 전투 로그 읽기
        else if (is_log_section && !line.empty())
        {
            all_logs_.push_back(line);
        }
    }
    file.close();
}

void LogManager::ResetStats()
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
    kill_counts_.clear();

    // 전체 전투 로그(파일 저장용) 초기화
    all_logs_.clear();

}

const std::map<std::string, int>& LogManager::GetKillCounts() const
{
    return kill_counts_;
}

std::vector<std::string> LogManager::GetStatsSummary() const
{
    std::vector<std::string> summary;

    // 총 처치 횟수 계산
    int total_kills = 0;
    for (const auto& k : kill_counts_) {
        total_kills += k.second;
    }

    summary.push_back("총 이동 횟수     : " + std::to_string(count_move_));
    summary.push_back("몬스터 조우 횟수 : " + std::to_string(count_encounter_));
    summary.push_back("총 공격 횟수     : " + std::to_string(count_attack_));
    summary.push_back("총 피격 횟수     : " + std::to_string(count_damage_));
    summary.push_back("몬스터 처치 횟수 : " + std::to_string(total_kills));
    summary.push_back("아이템 사용 횟수 : " + std::to_string(count_use_));
    summary.push_back("총 휴식 횟수     : " + std::to_string(count_rest_));
    summary.push_back("총 도망 횟수     : " + std::to_string(count_escape_));

    return summary;
}
