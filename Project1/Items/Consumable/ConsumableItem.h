#pragma once
#include "Item.h"

#include <string>

class Character;

class ConsumableItem : public IItem
{
protected:
	std::string name;
	ItemID id;
	std::string description;
	int count; // 소비 아이템은 개수로 관리
	int max_count; // 최대 개수 제한 

public:
	ConsumableItem(std::string _name, ItemID _id, std::string _description, int _max_count) : name(_name), id(_id), description(_description), count(1), max_count(_max_count) {}
	virtual ~ConsumableItem() = default;

	const std::string& GetName() const override { return name; }
	ItemID GetID() const override { return id; }
	const std::string& GetDesc() const override { return description; }
	ItemType GetType() const override { return ItemType::Consumable; }
	const int GetCount() const { return count; }
	const int GetMaxCount() const { return max_count; }
	void AddCount(int amount) { count = std::min(count + amount, max_count); } // 개수 추가 (최대 개수까지)

	void Use(Character& target) override = 0;
}; 
