#pragma once
#include "Item.h"
#include <string>
#include <unordered_map>

struct ItemData {
	std::string name;
	std::string desc;
	int price{};
};

class ItemDataBase
{
public:
	static void Initialize();
	static const ItemData& GetData(ItemID id);
	static int GetSellPrice(ItemID id);

private:
	static std::unordered_map<ItemID, ItemData> data;
	static constexpr float SELL_RATIO = 0.6f;
};

