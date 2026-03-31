#include "Character.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Item.h"
#include "Equippable/EquippableItem.h"
#include "Consumable/ConsumableItem.h"

Character::Character(std::string name) 

	: name(name), level(1), health(200), max_health(200), attack(30), bonus_attack(0), experience(0),
	gold(0), equipped_weapon(nullptr), equipped_armor(nullptr) {}


// 싱글톤
Character& Character::GetInstance(const std::string& name)
{
	static Character instance(name);
	return instance;
}

void Character::DisplayStatus() const
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Level: " << level << std::endl;
	std::cout << "Health: " << health << "/" << max_health << std::endl;
	std::cout << "Attack: " << attack << std::endl;
	std::cout << "Experience: " << experience << std::endl;
	std::cout << "Gold: " << gold << std::endl;
}

void Character::DisplayInventory() const
{
	std::cout << "Inventory:" << std::endl;
	for (size_t i = 0; i < inventory.size(); ++i)
	{
		std::cout << i + 1 << ". " << inventory[i]->GetName() << std::endl;
	}
}

void Character::LevelUp()
{
	if (level >= 10)
	{
		return;
	}
	level++;
	max_health += level * 20;		// 레벨에 비례하여 상승
	health = max_health;			// 체력을 최대치로 회복
	attack += level * 5;			// 공격력 증가
}

void Character::AddItem(std::unique_ptr<IItem> item)
{
	if (!item)
	{
		std::cout << "잘못된 아이템 아이디 입니다." << std::endl;
		return;
	}
	
	// 소비 아이템인 경우
	if(item->GetType () == ItemType::Consumable)
	{
		auto* new_item = static_cast<ConsumableItem*>(item.get());

		// 이미 인벤토리에 같은 소비 아이템이 있는지 확인
		for (auto& inv_item : inventory)
		{
			if (inv_item->GetID() == item->GetID() && inv_item->GetType() == ItemType::Consumable)
			{
				auto* existing_item = static_cast<ConsumableItem*>(inv_item.get());
				int available_space = existing_item->GetMaxCount() - existing_item->GetCount();	

				// 기존 아이템에 추가할 수 있는 공간이 있다면 새 아이템에서 개수를 옮겨 담음
				if (available_space > 0)
				{
					int transfer_count = std::min(available_space, new_item->GetCount());
					existing_item->AddCount(transfer_count);
					new_item->AddCount(-transfer_count); // 새 아이템에서 사용한 개수만큼 감소

					if (new_item->GetCount() <= 0)
					{
						return; // 모든 아이템이 기존 아이템에 합쳐졌으므로 추가할 필요 없음
					}
				}
			}
		}
	}
	inventory.push_back(std::move(item));
}

void Character::UseItem(size_t index)
{
	if (index >= inventory.size())	// 인벤토리에서 아이템을 사용하기 전에 유효한 인덱스인지 확인
	{
		std::cout << "잘못된 아이템 인덱스 입니다." << std::endl;
		return;
	}

	if(inventory[index]->GetType() == ItemType::Consumable)
	{
		auto* consumable = static_cast<ConsumableItem*>(inventory[index].get());
		consumable->Use(*this);

		// 소비 아이템은 개수가 0이 되면 인벤토리에서 제거
		if (consumable->GetCount() <= 0) 
		{
			inventory.erase(inventory.begin() + index);
		}
	}

	else if(inventory[index]->GetType() == ItemType::Weapon)
	{
		std::unique_ptr<IItem> old_weapon = EquipWeapon(std::move(inventory[index]));
		inventory.erase(inventory.begin() + index); // 사용한 아이템 제거

		if(old_weapon)
		{
			AddItem(std::move(old_weapon)); // 이전에 장착했던 무기를 인벤토리에 추가
		}
	}

	else if(inventory[index]->GetType() == ItemType::Armor)
	{
		std::unique_ptr<IItem> old_armor = EquipArmor(std::move(inventory[index]));
		inventory.erase(inventory.begin() + index); // 사용한 아이템 제거

		if(old_armor)
		{
			AddItem(std::move(old_armor)); // 이전에 장착했던 방어구를 인벤토리에 추가
		}
	}
}

void Character::GainGold(int total_gold)
{
	gold += total_gold;
}

void Character::GainExp(int total_exp)
{
	experience += total_exp;
	while (experience >= 100) 
	{
		experience -= 100; // 100만큼 소모하고 남은 건 유지
		LevelUp();         // 레벨업 스탯 반영
	}
}

void Character::TakeDamage(int damage) 
{
	health -= damage;
	if (health < 0) 
	{
		health = 0;  // 체력이 음수가 되지 않도록 조정
	}
}

void Character::ModifyMaxHealth(int amount) 
{
	max_health += amount;
	if (max_health < 1) 
	{
		max_health = 1; // 최대 체력이 1보다 작아지지 않도록 조정
	}
	if (health > max_health) 
	{
		health = max_health; // 현재 체력이 최대 체력을 초과하지 않도록 조정
	}
}

bool Character::IsDead() const 
{
	return health <= 0;
}

void Character::RestoreHealth(int amount) 
{
	health += amount;
	if (health > max_health) 
	{
		health = max_health;  // 최대 체력을 초과하지 않도록 조정
	}
}

void Character::IncreaseAttack(int amount) 
{
	attack += amount;
}

void Character::RemoveItem(size_t index)
{
	if (index >= inventory.size())	// 인벤토리에서 아이템을 제거하기 전에 유효한 인덱스인지 확인
	{
		std::cout << "잘못된 아이템 인덱스 입니다." << std::endl;
		return;
	}

	if (inventory[index]->GetType() == ItemType::Consumable)
	{
		auto* consumable = static_cast<ConsumableItem*>(inventory[index].get());
		consumable->AddCount(-1); // 개수 감소

		// 소비 아이템은 개수가 0이 되면 인벤토리에서 제거
		if (consumable->GetCount() <= 0)
		{
			inventory.erase(inventory.begin() + index);
		}
	}

	// 무기나 방어구 아이템은 인벤토리에서 제거
	else
	{
		inventory.erase(inventory.begin() + index);
	}
}

std::unique_ptr<IItem> Character::EquipWeapon(std::unique_ptr<IItem> new_weapon)
{
	if (new_weapon->GetType() != ItemType::Weapon) 
	{
		std::cout << "이 아이템은 무기가 아닙니다." << std::endl;
		return new_weapon; // 잘못된 아이템 반환
	}

	// 장착한 무기가 존재하면
	std::unique_ptr<IItem> old_weapon = UnequipWeapon(); // 기존 무기 제거

	// 새 무기 장착
	equipped_weapon = std::move(new_weapon);
	if (equipped_weapon)
	{
		auto* weapon = static_cast<EquippableItem*>(equipped_weapon.get());
		weapon->Equip(*this); // 새 무기 장착
	}

	return old_weapon; // 이전에 장착했던 무기 반환
}

std::unique_ptr<IItem> Character::EquipArmor(std::unique_ptr<IItem> new_armor)
{
	if (new_armor->GetType() != ItemType::Armor) 
	{
		std::cout << "이 아이템은 방어구가 아닙니다." << std::endl;
		return new_armor; // 잘못된 아이템 반환
	}
	
	// 장착한 방어구가 존재하면
	std::unique_ptr<IItem> old_armor = UnequipArmor(); // 기존 방어구 제거

	// 새 방어구 장착
	equipped_armor = std::move(new_armor);
	if (equipped_armor)
	{
		auto* armor = static_cast<EquippableItem*>(equipped_armor.get());
		armor->Equip(*this); // 새 방어구 장착
	}

	return old_armor; // 이전에 장착했던 방어구 반환
}

std::unique_ptr<IItem> Character::UnequipWeapon()
{
	if (!equipped_weapon) return nullptr; // 장착된 무기가 없는 경우 nullptr 반환

	auto* old_weapon = static_cast<EquippableItem*>(equipped_weapon.get());
	old_weapon->Unequip(*this); // 무기 효과 제거

	return std::move(equipped_weapon); // 이전에 장착했던 무기 반환
}

std::unique_ptr<IItem> Character::UnequipArmor()
{
	if (!equipped_armor) return nullptr; // 장착된 방어구가 없는 경우 nullptr 반환

	auto* old_armor = static_cast<EquippableItem*>(equipped_armor.get());
	old_armor->Unequip(*this); // 방어구 효과 제거

	return std::move(equipped_armor); // 이전에 장착했던 방어구 반환
}


void Character::ApplyAttackBuff(int amount)
{
	bonus_attack = std::max(bonus_attack, amount);
}

void Character::ClearBuffs()
{
	// 일회용 버프 초기화
	bonus_attack = 0;
}

void Character::ClearInventory() {
	inventory.clear();
}

void Character::Reset() {
	level = 1;
	health = 200;
	max_health = 200;
	attack = 30;
	bonus_attack = 0;
	experience = 0;
	gold = 0;

	UnequipWeapon();
	UnequipArmor();
	ClearInventory();
}