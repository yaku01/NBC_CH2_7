#pragma once
#include "Monster.h"


using namespace std;

class Orc : public Monster {

public:
	Orc(int level);
	void TakeDamage(int damage) override;
	string GetAsciiArtPath() const override;
};