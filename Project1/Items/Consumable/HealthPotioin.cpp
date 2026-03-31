#include "HealthPotion.h"

#include <string>

#include "Character.h" 

HealthPotion::HealthPotion() : health_restore(50), ConsumableItem("Health Potion", ItemID::HealthPotion, "체력을" + std::to_string(health_restore) + " 회복합니다", 3) {}


void HealthPotion::Use(Character& target) 
{
	target.RestoreHealth(health_restore);
	AddCount(-1); // 사용한 개수만큼 감소
}