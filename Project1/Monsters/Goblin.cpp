#include "Goblin.h"
#include<iostream>
#include<vector>

using namespace std;

Goblin::Goblin(int level) : Monster(level) {
    name = "Goblin";
    maxhealth = level * 80;
    health = maxhealth;
    attack = level * 13;
    speed = 0.8f;

    droptable.addItem(ItemID::HealthPotion, 0.3);
    droptable.addItem(ItemID::AttackBoost, 0.3);
    droptable.addItem(ItemID::Armor, 0.1);
    droptable.addItem(ItemID::Sword, 0.1);
}

void Goblin::TakeDamage(int damage) {
    health -= damage;
    if (health < 0)health = 0;
}

string Goblin::GetAsciiArtPath() const
{ 
    return "Resource/Monsters/Goblin.txt";
}
