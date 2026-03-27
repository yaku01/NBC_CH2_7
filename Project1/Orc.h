#pragma once
#include "Monster.h"


using namespace std;

class Orc : public Monster {

public:
	Orc(int level);
	void takeDamage(int damage) override;
};