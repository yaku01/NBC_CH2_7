#include "Slime.h"
#include<iostream>
using namespace std;

Slime::Slime(int level) : Monster(level) {
    name = "Slime";
    maxhealth = level * 30;
    health = maxhealth;
    attack = level * 5;

    droptable.addItem(ItemID::HealthPotion, 0.3);
    droptable.addItem(ItemID::AttackBoost, 0.3);
}


void Slime::TakeDamage(int damage) {
    health -= damage;

    if (health < 0)health = 0;


}

string Slime::GetAsciiArtPath() const
{
    return "Resource/Monsters/Slime.txt";
}
