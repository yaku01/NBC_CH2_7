#include "AttackBoost.h"

#include <iostream>

#include "Character.h"


AttackBoost::AttackBoost() : name("Attack Boost"), id(ItemID::AttackBoost), attack_increase(10) {}

std::string AttackBoost::GetName() const 
{
	return name;
}

ItemID AttackBoost::GetID() const 
{
	return id;
}

void AttackBoost::Use(Character& target) 
{
	target.IncreaseAttack(attack_increase);
}