#pragma once
#include "Item.h"

#include <string>

class Character;

class AttackBoost : public IItem
{
private:
	std::string name;
	ItemID id;
	int attack_increase;

public:
	AttackBoost();

	std::string GetName() const override;
	ItemID GetID() const override;

	void Use(Character& target) override;
};