#include "Goblin.h"
#include<iostream>
#include<vector>

using namespace std;

Goblin::Goblin(int level) : Monster(level){
    name = "Goblin";
    health = level*100;
    attack = level*15;

    droptable.addItem(ItemID::HealthPotion, 0.5);
    droptable.addItem(ItemID::AttackBoost, 0.5);
}

void Goblin::takeDamage(int damage) {
    health -= damage;
}