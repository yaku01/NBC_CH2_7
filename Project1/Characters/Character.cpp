#include "Character.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Item.h"

Character::Character(std::string name) : name(name), level(1), health(200), max_health(200), attack(30), experience(0), gold(0) {}

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
	inventory.push_back(std::move(item));
}

void Character::UseItem(size_t index)
{
	if (index >= inventory.size())	// 인벤토리에서 아이템을 사용하기 전에 유효한 인덱스인지 확인
	{
		std::cout << "잘못된 아이템 인덱스 입니다." << std::endl;
		return;
	}

	inventory[index]->Use(*this);
	inventory.erase(inventory.begin() + index); // 사용한 아이템 제거
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