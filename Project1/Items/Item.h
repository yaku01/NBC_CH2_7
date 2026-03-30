#pragma once
#include <string>

class Character;

enum class ItemID 
{
	None = 0,
	HealthPotion = 101,
	AttackBoost = 102,
};

enum class ItemType
{
	Undefined = 0,
	Consumable,
	Weapon,
	Armor,
};

class IItem
{
public:
	virtual ~IItem() = default;
	virtual void Use(Character& target) = 0;

	// getters
	virtual const std::string& GetName() const = 0;
	virtual ItemID GetID() const = 0;
	virtual const std::string& GetDesc() const = 0;
	virtual ItemType GetType() const = 0;
};