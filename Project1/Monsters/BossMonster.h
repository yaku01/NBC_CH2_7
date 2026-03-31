#include "Monster.h"

class BossMonster : public Monster
{
public:
	BossMonster(int level);
	~BossMonster() = default;

private:


	// Monster을(를) 통해 상속됨
	void TakeDamage(int damage) override;

	string GetAsciiArtPath() const override;

};
