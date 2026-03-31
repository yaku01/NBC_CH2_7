#pragma once
#include "Item.h"
#include "EquippableItem.h"

class Character;

class Armor : public EquippableItem
{
private:
	int max_health_increase; 

public:
	Armor(std::string _name, ItemID _id, std::string _description, int _power);

	void Use(Character& target) override;
	void Equip(Character& target) override;
	void Unequip(Character& target) override;
};
