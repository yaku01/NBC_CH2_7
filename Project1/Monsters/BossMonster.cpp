#include "BossMonster.h"
#include "Common/common.h"

BossMonster::BossMonster(int level) : Monster(level)
{
    name = "마왕";
    double weight = RandomUtil::GetRange(1.4, 1.6);
    //maxhealth = static_cast<int>(level * 15 * weight);
    maxhealth = static_cast<int>(level * 130 * weight);
    health = maxhealth;
    attack = static_cast<int>(level * 15 * weight);
    speed = 2.f;
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
