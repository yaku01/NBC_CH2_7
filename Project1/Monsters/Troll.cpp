#include "Troll.h"
#include<iostream>
using namespace std;

Troll::Troll(int level) : Monster(level) {
    name = "Troll";
    maxhealth = level * 80;
    health = maxhealth;
    attack = level * 10;

    droptable.addItem(ItemID::HealthPotion, 0.3);
    droptable.addItem(ItemID::AttackBoost, 0.3);
}



void Troll::TakeDamage(int damage) {

    health -= damage;
    if (health < 0)health = 0;

}

string Troll::GetAsciiArtPath() const
{
    return "Resource/Monsters/Troll.txt";
}
