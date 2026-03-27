#pragma once
#include "BaseUI.h"
#include <unordered_map>  // 킬보드에서 몬스터 이름과 킬 수를 매핑하기 위해 추가

class MessageUI : public BaseUI
{
public:
	MessageUI(int x, int y, int w, int h);

	void Render() override;

private:
	std::string top_border;
	std::string bottom_border;
};


class LogUI : public BaseUI
{
public:
	LogUI(int x, int y, int w, int h);

	void Render() override;
	void AddMessage(std::string_view msg) override;

private:
	std::string top_border;
	std::string bottom_border;
};

// 킬보드 UI 클래스
class KillBoardUI : public BaseUI	
{
public:
	KillBoardUI(int x, int y, int w, int h);

	void Render() override;
	void AddKill(const std::string& monster_name);

private:
	std::string top_border;
	std::string bottom_border;
	std::unordered_map<std::string, int> kill_count_;
};