#pragma once
#include "Monster.h"


using namespace std;

class Slime : public Monster {

public:
	Slime(int level);
	void TakeDamage(int damage) override;
	string GetAsciiArtPath() const override;
}; 
