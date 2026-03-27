#pragma once
#include "Monster.h"


using namespace std;

class Goblin : public Monster {

public:
	Goblin(int level);
	void takeDamage(int damage) override;
};