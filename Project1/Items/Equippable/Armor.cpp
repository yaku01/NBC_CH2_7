#include "Armor.h"

#include <string>

#include "Character.h"

Armor::Armor(std::string _name, ItemID _id, std::string _description, int _power)
	: EquippableItem(_name, _id, _description, ItemType::Armor), max_health_increase(_power) {
}

void Armor::Use(Character& target)
{
	// 방어구는 장착 아이템이므로 Use()에서는 아무 동작도 하지 않습니다.
	// 출력 메시지는 필요시 추가할 수 있습니다.
	// std::cout << "방어구를 장착했습니다." << std::endl;
}

void Armor::Equip(Character& target)
{
	target.ModifyMaxHealth(max_health_increase);
}

void Armor::Unequip(Character& target)
{
	target.ModifyMaxHealth(-max_health_increase);
} 
