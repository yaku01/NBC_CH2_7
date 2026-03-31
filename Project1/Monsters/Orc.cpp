#include "Orc.h"
#include<iostream>
using namespace std;

Orc::Orc(int level) : Monster(level) {
    name = "Orc";
    maxhealth = level * 150;
    health = maxhealth;
    attack = level * 17;
    speed = 0.5f;

    droptable.addItem(ItemID::HealthPotion, 0.3);
    droptable.addItem(ItemID::AttackBoost, 0.3);
}



void Orc::TakeDamage(int damage) {

    health -= damage;
    if (health < 0)health = 0;

}
 
string Orc::GetAsciiArtPath() const
{
    return "Resource/Monsters/Orc.txt";
}
