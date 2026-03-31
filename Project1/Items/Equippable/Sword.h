#pragma once
#include "Item.h"
#include "EquippableItem.h"

class Character;

class Sword : public EquippableItem
{
private:
	int attack_increase;

public:
	Sword(std::string _name, ItemID _id, std::string _description, int _power);

	void Use(Character& target) override;
	void Equip(Character& target) override;
	void Unequip(Character& target) override;
}; 
