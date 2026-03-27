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
	int GetMaxHealth() const { return max_hp; }
	std::string GetName() const { return name; }

	void SetVisible(bool visible) { is_visible = visible; }

	bool IsDead() const { return (hp <= 0); }
	bool IsVisible() const { return is_visible; }

private:
	int attack = 3;
	int hp = 20;
	int max_hp = 20;
	std::string name = "orc";
	bool is_visible = false;
};

