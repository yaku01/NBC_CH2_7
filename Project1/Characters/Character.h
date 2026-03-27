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
	int health;
	int max_health;
	int attack;
	int experience;
	int gold;
	std::vector<std::unique_ptr<IItem>> inventory;

	// 생성자는 private으로 선언하여 외부에서 직접 인스턴스를 생성하지 못하도록 함
	Character(std::string name);

public:
	// 싱글톤 패턴을 위해 복사 생성자와 대입 연산자 삭제
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;
	static Character& GetInstance(const std::string& name = "Player");

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

	// getters
	int GetLevel() const { return level; }

	int GetHealth() const { return health; }

	int GetMaxHealth() const { return max_health; }

	int GetAttack() const { return attack; }

	int GetExperience() const { return experience; }

	int GetGold() const { return gold; }

	const std::string& GetName() const { return name; }

	const std::vector<std::unique_ptr<IItem>>& GetInventory() const { return inventory; }

	// setters
	void SetLevel(int new_level) { level = new_level; }

	void SetHealth(int new_health) { health = new_health; }

	void SetMaxHealth(int new_max_health) { max_health = new_max_health; }

	void SetAttack(int new_attack) { attack = new_attack; }

	void SetExperience(int new_experience) { experience = new_experience; }

	void SetGold(int new_gold) { gold = new_gold; }
};