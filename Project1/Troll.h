#pragma once
#include "Monster.h"


using namespace std;

class Troll : public Monster {

public:
	Troll(int level);
	void takeDamage(int damage) override;
};