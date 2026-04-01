#include "Troll.h"
#include<iostream>
using namespace std;

Troll::Troll(int level) : Monster(level) {
    name = "Troll";
    maxhealth = level * 60;
    health = maxhealth;
    attack = level * 10;
    speed = 1.f;

    droptable.addItem(ItemID::HealthPotion, 0.3);
    droptable.addItem(ItemID::AttackBoost, 0.3);
    droptable.addItem(ItemID::LeatherArmor, 0.1);
    droptable.addItem(ItemID::WoodSword, 0.1);
}



void Troll::TakeDamage(int damage) {

    health -= damage;
    if (health < 0)health = 0;

}

string Troll::GetAsciiArtPath() const 
{
    return "Resource/Monsters/Troll.txt";
}
