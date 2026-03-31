#include "BossMonster.h"
#include "Common/common.h"

BossMonster::BossMonster(int level) : Monster(level)
{
    name = "¸¶¿Õ";
    double weight = RandomUtil::GetRange(1.4, 1.6);
    maxhealth = static_cast<int>(level * 15 * weight);
    health = maxhealth;
    attack = static_cast<int>(level * 17 * weight);
}

void BossMonster::TakeDamage(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0;
}

string BossMonster::GetAsciiArtPath() const
{
    return "Resource/Monsters/Demon Lord.txt";
}
