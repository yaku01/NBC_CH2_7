#pragma once
#include <deque>
#include <string>

class Character;

class BaseUI
{
public:
	BaseUI(int x, int y, int w, int h);
	BaseUI(int x, int y);
	virtual ~BaseUI() = default;

	virtual void AddContents(std::string_view msg);
	void LoadAsciiArt(const std::string& path);
	void Clear();

	void SetVisible(bool valid);
	void ToggleVisible();
	bool IsVisible() const;

	virtual void Render() = 0;
	virtual void Update(float delta_time) {}

	//전체 로그 저장용 
	std::deque<std::string> all_contents; 
	const std::deque<std::string>& GetAllContents() const { return all_contents; }

protected:
	int start_x;
	int start_y;
	int width;
	int height;
	int max_lines;
	bool is_visible;
	std::deque<std::string> contents;
};
