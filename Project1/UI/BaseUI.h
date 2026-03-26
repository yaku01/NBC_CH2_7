#pragma once
#include <deque>
#include <string>

class BaseUI
{
public:
	BaseUI(int x, int y, int w, int h);
	virtual ~BaseUI() = default;

	virtual void AddMessage(std::string_view msg);
	void Clear();

	void SetVisible(bool valid);
	void ToggleVisible();
	bool IsVisible() const;

	virtual void Render() = 0;

protected:
	int start_x;
	int start_y;
	int width;
	int height;
	int max_lines;
	bool is_visible;
	std::deque<std::string> messages;
};

