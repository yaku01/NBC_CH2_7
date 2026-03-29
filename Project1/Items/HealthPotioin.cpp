#include "HealthPotion.h"

#include <string>

#include "Character.h" 

HealthPotion::HealthPotion() : name("Health Potion"), id(ItemID::HealthPotion), health_restore(50) 
{
	
	description = "체력을" + std::to_string(health_restore) + " 회복합니다";
}

std::string HealthPotion::GetName() const 
{
	return name;
}

ItemID HealthPotion::GetID() const 
{
	return id;
}

std::string HealthPotion::GetDesc() const
{
	return description;
}

void HealthPotion::Use(Character& target) 
{
	target.RestoreHealth(health_restore);
}