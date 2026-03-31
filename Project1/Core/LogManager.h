#pragma once
#include <string>
#include <string_view>
#include <map>
#include <vector>


class LogManager
{
public:
	static LogManager& GetInstance() {
		static LogManager instance;
		return instance;
	}
	
	LogManager(const LogManager&) = delete;
	LogManager& operator=(const LogManager&) = delete;

	void AddLog(std::string_view msg);
	void AddKill(const std::string& monster_name);

	void SaveLogToFile(const std::string& filename, const std::string& player_name);
	void LoadLogFromFile(const std::string& filename, const std::string& player_name);
	void ResetStats();
	
	const std::map<std::string, int>& GetKillCounts() const;
	std::vector<std::string> GetStatsSummary() const;

private:
	int count_attack_ = 0;
	int count_damage_ = 0;
	int count_encounter_ = 0;
	int count_move_ = 0;
	int count_rest_ = 0;
	int count_reward_ = 0;
	int count_escape_ = 0;
	int count_death_ = 0;
	int count_use_ = 0;

	std::map<std::string, int> kill_counts_;   // 몬스터 처치 수 데이터
	std::vector<std::string> all_logs_;     // 전체 텍스트 로그 데이터

	LogManager() = default;
	~LogManager() = default;
};

