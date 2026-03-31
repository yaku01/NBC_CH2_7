#pragma once
#include <string>
#include <vector>
#include <memory>

class IItem;

class Character
{
private:
	std::string name;
	int level;
	const int max_level = 10;
	int health;
	int max_health; 
	int attack;
	int bonus_attack;
	int experience;
	int gold;
    float speed;
	std::vector<std::unique_ptr<IItem>> inventory; 
	std::unique_ptr<IItem> equipped_weapon;
	std::unique_ptr<IItem> equipped_armor;

	// 생성자는 private으로 선언하여 외부에서 직접 인스턴스를 생성하지 못하도록 함
	Character(std::string name);

public:
	// 싱글톤 패턴을 위해 복사 생성자와 대입 연산자 삭제
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;
	static Character& GetInstance(const std::string& name = "Player");

	void ClearInventory();

	void DisplayStatus() const;

	void DisplayInventory() const;

	void LevelUp();

	void AddItem(std::unique_ptr<IItem> item);

	void UseItem(size_t index);

	void GainGold(int total_gold);

	void GainExp(int total_exp);

	void TakeDamage(int damage);

	bool IsDead() const;

	void RestoreHealth(int amount);

	void IncreaseAttack(int amount);

	void RemoveItem(size_t index);
	
	void ModifyMaxHealth(int amount);

	void Reset();

	std::unique_ptr<IItem> EquipWeapon(std::unique_ptr<IItem> new_weapon);

	std::unique_ptr<IItem> EquipArmor(std::unique_ptr<IItem> new_armor);

	std::unique_ptr<IItem> UnequipWeapon();

	std::unique_ptr<IItem> UnequipArmor();

	void ApplyAttackBuff(int amount);

	void ClearBuffs();

	bool IsMaxLevel() const;

	// getters
	int GetLevel() const { return level; }

	int GetHealth() const { return health; }

	int GetMaxHealth() const { return max_health; }

	int GetTotalAttack() const { return attack + bonus_attack; }

	int GetAttack() const { return attack; }

	int GetBonusAttack() const { return bonus_attack; }

	int GetExperience() const { return experience; }

	int GetGold() const { return gold; }

	const std::string& GetName() const { return name; }

	const std::vector<std::unique_ptr<IItem>>& GetInventory() const { return inventory; }

	const IItem* GetEquippedWeapon() const { return equipped_weapon.get(); }

	const IItem* GetEquippedArmor() const { return equipped_armor.get(); }

    float GetSpeed() const { return speed; }

	// setters
	void SetLevel(int new_level) { level = new_level; }

	void SetHealth(int new_health) { health = new_health; }

	void SetMaxHealth(int new_max_health) { max_health = new_max_health; }

	void SetAttack(int new_attack) { attack = new_attack; }

	void SetExperience(int new_experience) { experience = new_experience; }

	void SetGold(int new_gold) { gold = new_gold; }

	void SetName(const std::string& newName) { name = newName; }
};
