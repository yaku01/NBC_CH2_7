#pragma once
#include "BaseUI.h"

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
