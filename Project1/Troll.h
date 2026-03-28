#pragma once
#include "Monster.h"


using namespace std;

class Troll : public Monster {

public:
	Troll(int level);
	void TakeDamage(int damage) override;
	string GetAsciiArtPath() const override;
};