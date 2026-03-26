#include "HealthPotion.h"

#include <string>

#include "Characters/Character.h"

HealthPotion::HealthPotion() : name("Health Potion"), id(ItemID::AttackBoost), health_restore(50) {}

std::string HealthPotion::GetName() const 
{
	return name;
}

ItemID HealthPotion::GetID() const 
{
	return id;
}

void HealthPotion::Use(Character& target) 
{
	target.RestoreHealth(health_restore);
}