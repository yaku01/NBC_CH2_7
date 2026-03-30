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

public:
	ConsumableItem(std::string _name, ItemID _id, std::string _description) : name(_name), id(_id), description(_description) {}
	virtual ~ConsumableItem() = default;

	const std::string& GetName() const override { return name; }
	ItemID GetID() const override { return id; }
	const std::string& GetDesc() const override { return description; }
	ItemType GetType() const override { return ItemType::Consumable; }

	void Use(Character& target) override = 0;
};