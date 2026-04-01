#include "ItemDataBase.h"

std::unordered_map<ItemID, ItemData> ItemDataBase::data;

void ItemDataBase::Initialize()
{
	data[ItemID::HealthPotion] = { "HealthPotion", "체력을 50 회복합니다.", 10 };
	data[ItemID::AttackBoost] = { "AttackBoost", "다음 전투에서 공격력이 10 증가합니다.", 10 };
	data[ItemID::WoodSword] = { "Wood Sword", "공격력이 5 증가합니다.", 75 };
	data[ItemID::Sword] = { "Sword", "공격력이 15 증가합니다.", 150 }; 
	data[ItemID::LeatherArmor] = { "Leather Armor", "최대 체력이 20 증가합니다.", 75 };
	data[ItemID::Armor] = { "Armor", "최대 체력이 50 증가합니다.", 125 };
}

const ItemData& ItemDataBase::GetData(ItemID id)
{
	return data[id];
}

int ItemDataBase::GetSellPrice(ItemID id)
{
	const ItemData& data = GetData(id);
	return std::max(1, static_cast<int>(data.price * SELL_RATIO));
}
