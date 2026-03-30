#pragma once
#include <string>

class Character;

enum class ItemID 
{
	None = 0,

	// 소비 아이템 ID는 100번대
	HealthPotion = 101,
	AttackBoost = 102,

	// 무기 아이템 ID는 200번대 
	WoodSword = 201,
	Sword = 202,

	// 방어구 아이템 ID는 300번대로 구분
	LeatherArmor = 301,
	Armor = 302,
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