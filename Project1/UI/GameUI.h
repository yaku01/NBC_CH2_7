#pragma once
#include "BaseUI.h"
#include "Items/Item.h"
#include <unordered_map>  // 킬보드에서 몬스터 이름과 킬 수를 매핑하기 위해 추가
#include <vector>
#include <string>

class Character;
class Monster;

// 테두리 있는 UI
class BorderUI : public BaseUI
{
public:
	BorderUI(int x, int y, int w, int h);
	virtual ~BorderUI() = default;

	virtual void Render() override;
	
protected:
	void ClearBackGround();

private:
	std::string top_border;
	std::string bottom_border;
};


class LogUI : public BorderUI
{
public:
	LogUI(int x, int y, int w, int h);
	~LogUI() = default;

	void AddContents(std::string_view msg) override;
};


class CharacterInfoUI : public BorderUI
{
public:
	CharacterInfoUI(int x, int y, int w, int h);
	~CharacterInfoUI() = default;

	void Render() override;
};


class ItemListUI : public BorderUI
{
public:
	ItemListUI(int x, int y, int w, int h);
	virtual ~ItemListUI() = default;

	void NextPage(int total_items);
	void PrevPage();
	int GetCurrentPage() const;
	int GetItemsPerPage() const;

protected:
	int current_page = 0;
	const int ITEMS_PER_PAGE = 9;

	void RenderTitle(const std::string& title);
	void RenderPage(int total_items);
	int GetStartIndex() const;
	int GetEndIndex(int total_items) const;
};


class InventoryUI : public ItemListUI
{
public:
	InventoryUI(int x, int y, int w, int h);
	virtual ~InventoryUI() = default;

	void Render() override;
	void ToggleActive();
	bool IsActive() const;

private:
	bool is_active = false;
};


class ShopUI : public ItemListUI
{
public:
	ShopUI(int x, int y, int w, int h);
	~ShopUI() = default;

	void Render() override;
	void SetMode(bool is_buy_mode, const std::vector<ItemID>* item_ids = nullptr);

private:
	bool is_buy_mode = true;
	const std::vector<ItemID>* shop_items = nullptr;
};


class ItemConfirmUI : public BorderUI 
{
public:
	ItemConfirmUI(int x, int y, int w, int h);
	~ItemConfirmUI() = default;

	void Render() override;
	void SetTarget(ItemID id);
	void SetActionText(const std::string& action);

private:
	ItemID target = ItemID::None;
	std::string action_text;
};


// 아스키아트만 출력하는 UI
class AsciiUI : public BaseUI
{
public:
	AsciiUI(int x, int y);
	virtual ~AsciiUI() = default;

	virtual void Render() override;
};


// 아스키아트 + info 출력하는 UI
// Character와 Monster의 상위 클래스가 있다면 아래 두 클래스 합치기 가능
class CharacterUI : public AsciiUI
{
public:
	CharacterUI(int x, int y);
	~CharacterUI() = default;

	void Render() override;
	void SetTarget(const Character* target);

private:
	const Character* target = nullptr;
};


class MonsterUI : public AsciiUI
{
public:
	MonsterUI(int x, int y);
	~MonsterUI() = default;

	void Render() override;
	void SetTarget(const Monster* target);

private:
	const Monster* target = nullptr;
};


// 킬보드 UI 클래스
class KillBoardUI : public BorderUI
{
public:
	KillBoardUI(int x, int y, int w, int h);
     
	void Render() override;
};


class UpdateUI : public BaseUI
{
public:
	UpdateUI(int x, int y, int w, int h, float max_time); 
	virtual ~UpdateUI() = default;

	virtual void Update(float delta_time) override;
	virtual void Render() = 0;

protected:
	float time;
	float max_time;
};



// 연출을 위한 ui
class WipeUI : public UpdateUI
{
public:
	WipeUI(int x, int y, int w, int h, float max_time);
	~WipeUI() = default;

	void Render() override;
};



class NoiseUI : public UpdateUI
{
public:
	NoiseUI(int x, int y, int w, int h, float max_time);
	~NoiseUI() = default;

	void Update(float delta_time) override;
	void Render() override;

private:
	const int block_w = 12;	// 블록의 가로 크기
	const int block_h = 6;  // 블록의 세로 크기

	int grid_cols;			// 가로 블록 개수
	int grid_rows;			// 세로 블록 개수
	int total_blocks;		// 총 블록 개수

	std::vector<int> indices;		// 화면내 그리드를 1차원 index로 봄
	std::vector<bool> is_filled;	// index가 채워졌는지 확인
};
