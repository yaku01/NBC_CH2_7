#pragma once
#include <string>

class Character;

enum class ItemID 
{
	None = 0,
	HealthPotion = 101,
	AttackBoost = 102,
};

class IItem
{
public:
	virtual ~IItem() = default;
	virtual void Use(Character& target) = 0;

	// getters
	virtual std::string GetName() const = 0;
	virtual ItemID GetID() const = 0;
};