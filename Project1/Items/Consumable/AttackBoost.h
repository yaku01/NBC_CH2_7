#pragma once
#include "Item.h"
#include "ConsumableItem.h"

#include <string>

class Character;

class AttackBoost : public ConsumableItem
{
private:
	int attack_increase;

public:
	AttackBoost(); 

	void Use(Character& target) override;
};
