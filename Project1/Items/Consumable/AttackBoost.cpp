#include "AttackBoost.h"

#include <iostream>

#include "Character.h"


AttackBoost::AttackBoost() : attack_increase(10), ConsumableItem("Attack Boost", ItemID::AttackBoost, "다음 전투에서 공격력이 "+ std::to_string(attack_increase) + " 증가합니다.") {}

void AttackBoost::Use(Character& target) 
{
	target.IncreaseAttack(attack_increase);
}