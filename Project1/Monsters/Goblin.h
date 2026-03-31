#pragma once
#include "Monster.h"


using namespace std;

class Goblin : public Monster {

public:
	Goblin(int level);
	void TakeDamage(int damage) override;
	string GetAsciiArtPath() const override;
}; 
