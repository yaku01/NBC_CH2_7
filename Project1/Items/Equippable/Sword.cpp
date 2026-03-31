#include "Sword.h"

#include <string>

#include "Character.h"

Sword::Sword(std::string _name, ItemID _id, std::string _description, int _power)
	: EquippableItem(_name, _id, _description, ItemType::Weapon), attack_increase(_power) {}

void Sword::Use(Character& target)
{	
	// 검은 장착 아이템이므로 Use()에서는 아무 동작도 하지 않습니다.
	// 출력 메시지는 필요시 추가할 수 있습니다.
	// std::cout << "검을 장착했습니다." << std::endl;
}

void Sword::Equip(Character& target)
{
	target.IncreaseAttack(attack_increase);
}

void Sword::Unequip(Character& target)
{
	target.IncreaseAttack(-attack_increase);
} 
