#pragma once
class Character
{
public:
	Character() = default;
	~Character() = default;

	void TakeDamage(int damage) {
		hp -= damage;
		if (hp <= 0) {
			hp = 0;
		}
	}
	void GainGold(int reward_gold) {
		gold += reward_gold;
	}
	void GainExp(int reward_exp) {
		experience += reward_exp;
	}

	int GetAttack() const { return attack; }
	int GetHp() const { return hp; }
	int GetMaxHp() const { return max_hp; }

private:
	int attack = 10;
	int hp = 100;
	int max_hp = 100;
	int gold = 0;
	int experience = 0;
	int level = 1;
};

