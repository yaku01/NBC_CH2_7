#pragma once
#include "Item.h"

#include <string>

class Character;

class EquippableItem : public IItem
{
protected:
	std::string name;
	ItemID id;
	std::string description;
	ItemType type;

public:
	EquippableItem(std::string _name, ItemID _id, std::string _description, ItemType _type) 
		: name(_name), id(_id), description(_description), type(_type)  {}
	virtual ~EquippableItem() = default;

	const std::string& GetName() const override { return name; }
	ItemID GetID() const override { return id; }
	const std::string& GetDesc() const override { return description; }
	ItemType GetType() const override { return type; }

	void Use(Character& target) override = 0;
	virtual void Equip(Character& target) = 0;
	virtual void Unequip(Character& target) = 0;
}; 
