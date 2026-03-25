#pragma once
class Monster
{
public:
	Monster() {}
	~Monster() {}

	void TakeDamage(int damage) {
		hp -= damage;
		if (hp <= 0) {
			hp = 0;
		}
	}

	int GetAttack() const { return attack; }
	int GetHealth() const { return hp; }


private:
	int attack = 3;
	int hp = 20;
	int max_hp = 20;
};

