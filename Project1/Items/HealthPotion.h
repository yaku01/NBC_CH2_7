#pragma once
#include "Item.h"
#include "ConsumableItem.h"

#include <string>

class Character;

class HealthPotion : public ConsumableItem
{
private:
	int health_restore;

public:
	HealthPotion();
	void Use(Character& target) override;
};